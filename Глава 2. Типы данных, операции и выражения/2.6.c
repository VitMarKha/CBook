#include <stdio.h>

void		printfbit(unsigned n);
unsigned	setbits(unsigned x, int p, int n, unsigned y);

int		main(void)
{
	printf("76543210\n");

	unsigned c1 = 'f';
	printfbit(c1);

	unsigned c2 = 'z';
	printfbit(c2);

	printfbit(setbits(c1, 5, 3, c2));
	return (0);
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

/* setbits: x получает n правых бит из y, начиная с p-й позиции */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	return ( (~0 << (p+1)) & x ) | ( ~(~0 << (p+1-n)) & x ) |
			(~(~0 << n) & y) << (p+1-n);
}
