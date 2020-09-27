#include <stdio.h>

#define swap(t, x, y)\
{\
t tmp;\
tmp = x;\
x = y;\
y = tmp;\
}\

int	main(void)
{
	int	a;
	int	b;

	a = 3;
	b = 7;
	swap(int, a, b);
	printf("a = %d\nb = %d", a, b);
	return (0);
}
