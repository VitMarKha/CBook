#include <stdio.h>

void		printfbit(unsigned n);
unsigned 	rightrot(unsigned x, int n);

int		main(void)
{
	printf("76543210\n\n");

	unsigned c = 'f';
	printfbit(c);

	printfbit(rightrot(c, 3));

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

/* rightrot: сдвиг x на n вправо */
unsigned rightrot(unsigned x, int n)
{
	return ((~(~0 << n) & x) << (8-n)) | x >> n;
}
