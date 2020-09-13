#include <stdio.h>

#define TRUE 1
#define FALSE 0

int	main(void)
{
	if (getchar() != EOF)
	{
		printf("%d", TRUE);
	}
	else
	{
		printf("%d", FALSE);
	}
	return (0);
}
