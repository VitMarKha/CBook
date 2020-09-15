#include <stdio.h>

void		printfbit(unsigned n);
unsigned 	invert(unsigned x, int p, int n);

int		main(void)
{
	printf("76543210\n");

	unsigned c = 'f';
	printfbit(c);

	printfbit(invert(c, 5, 3));

	return 0;
}

/* printfbit: выводит число в двоичном представлении */
void printfbit(unsigned n)
{
	int i;
	
	i = 7;
	while (i >= 0)
	{
		printf("%d", (n >> i) & 1);
		--i;
	}
	printf("\n");
}

/* invert: инвертирует n бит из x, начиная с p-й позиции */
 unsigned invert(unsigned x, int p, int n)
 {
	 return ( ((~x >> (p+1-n)) & ~(~0 << n)) << (p+1-n) ) |
			 (~( ((~0 >> (p+1-n)) & ~(~0 << n)) << (p+1-n) ) & x);
 }
