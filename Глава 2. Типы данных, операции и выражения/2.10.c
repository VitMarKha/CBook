#include <stdio.h>

int lower(int c);

int	main(void)
{
	int x = 'K';
	printf("%c", lower(x));
	return 0;
}

/* lower: преобразует символ с в нижний регистр, только ASCII */
int lower(int c)
{
	return (c >= 'A' && c <= 'Z') ? c += 32 : c;
}
