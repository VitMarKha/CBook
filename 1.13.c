#include <stdio.h>

#define IN 1
#define OUT 0

int	main(void)
{
	int	c;
	int	status;

	status = OUT;
	while ((c = getchar()) != EOF)
	{
		if (c == ' ' || c == '\t' || c == '\n')
		{
			status = OUT;
			putchar('\n');
		}
		else
		{
			status = IN;
		}
		if (status == IN)
		{
			putchar('*');
		}
	}
	return (0);
}
