#include <stdio.h>

int bitcount(unsigned x);
int fast_bitcount(unsigned x);

int	main(void)
{
	printf("%d",fast_bitcount(11));
	return 0;
}

/* bitcount подсчитывает единицы в двоичной записи x */
int bitcount(unsigned x)
{
	int b;

	b = 0;
	while (x != 0)
	{
		if (x & 01)
			b++;
		x >>= 1;
	}
	return b;
}

/* fast_bitcount быстрее подсчитывает единицы в двоичной записи x */
int fast_bitcount(unsigned x)
{
	int b;

	b = 0;
	while (x != 0)
	{
		x &= (x - 1);
		b++;
	}
	return b;
}
