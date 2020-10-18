#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXBYTES 10240 /* макс. число байт для запроса */
#define NALLOC 1024    /* миним. число единиц памяти для запроса */

typedef long Align;        /* для выравнивания по границе long */

union header {             /* заголовок блока: */
	struct {
		union header *ptr; /* след. блок в списке свободных */
		unsigned size;     /* размер этого блока */
	} s;
	Align x; /* принудительное выравнивание блока */
};

typedef union header Header;

static Header base;          /* пустой список для нач. запуска */
static Header *freep = NULL; /* начало в списке своб. блоков */
static unsigned maxallocsize;  /* максимальный размер выделенного блока */

void *my_malloc(unsigned);
void my_free(void *);

int main(void)
{
	int *ptr_one;

	ptr_one = (int *) my_malloc(sizeof(int));

	if (ptr_one == 0) {
		printf("error: Out of memory\n");
		exit(1);
	}

	*ptr_one = 25;
	printf("%d\n", *ptr_one);

	my_free(ptr_one);

	return 0;
}

static Header * my_morecore(unsigned);

/* malloc: универсальный распределитель памяти с проверкой */
void *my_malloc(unsigned nbytes)
{
	Header *p, *prevp;
	Header *morecore(unsigned);
	unsigned nunits;

	if (nbytes > MAXBYTES) {
		printf("error: превышен максимальный размер запроса %d\n", MAXBYTES);
		return NULL;
	}

	nunits = (nbytes + sizeof(Header) - 1 ) / sizeof (Header) + 1;
	if ((prevp = freep) == NULL) { /* списка своб. памяти еще нет */
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {      /* достаточно большой */
			if (p->s.size == nunits)    /* точно нужного размера */
				prevp->s.ptr = p->s.ptr;
			else {                      /* отрезаем хвостовую часть */
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if (p == freep)                 /* прошли полный цикл по списку */
			if ((p = my_morecore(nunits)) == NULL)
				return NULL; /* больше памяти нет */
	}
}

/* morecore: запрашивает у системы дополнительную память */
static Header * my_morecore(unsigned nu)
{
	char *cp;
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1) /* больше памяти нет. */
		return NULL;
	up = (Header *) cp;
	maxallocsize = ((up->s.size = nu) > maxallocsize) ? up->s.size : maxallocsize;
	my_free((void *)(up+1));
	return freep;
}

/* free: включает блок в список свободной памяти */
void my_free(void *ap)
{
	Header *bp, *p;

	bp = (Header *) ap -1; /* указатель на заголовок блока */
	
	if (bp->s.size <= 0 || bp->s.size > maxallocsize) {
		printf("error: не могу освободить блок размером %u байт \n", maxallocsize);
		exit(1);
	}
	
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break; /* освобождаем блок в начале или в конце */

	if (bp + bp->s.size == p->s.ptr) {  /* слить с верхним */
		bp->s.size += p->s.ptr->s.size; /* соседом */
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) { /* слить с нижним соседом */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}

unsigned bfree(char *p, unsigned n)
 {
	Header *bp;

	if (n < sizeof(Header))
		return 0;
	bp = (Header *) p;
	bp->s.size = n / sizeof(Header);
	my_free((void *)(bp+1));
	return bp->s.size;
 }
