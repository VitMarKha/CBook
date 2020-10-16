#include <stdio.h>

#define isup1(c) (c >= 'A' && c <= 'Z')

int isup2(char c);

int main()
{
	if (isup1('A'))
		printf("Macro works\n");
	if (!isup2('a'))
		printf("Func works\n");
   return 0;
}

int isup2(char c)
{
	return (c >= 'A' && c <= 'Z');
}
