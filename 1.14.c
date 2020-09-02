#include <stdio.h>

int	main(void)
{
	int	c;
	int i;
	int digit[10];
	int tab = 0;
	int other = 0;
	
	for (i = 0; i < 10; ++i)
	{
		digit[i] = 0;
	}
	while ((c = getchar()) != EOF)
	{
		if (c >= '0' && c <= '9')
		{
			++digit[c - '0'];
		}
		else if (c == ' ' || c == '\t' || c == '\n')
		{
			++tab;
		}
		else
		{
			++other;
		}
	}
//	printf("Digit bar chart:\n");
	int j = 0;

	for(i = 0; i < 10; ++i)
	{
		if (digit[i] != 0)
		{
			while (j < digit[i])
			{
				putchar('*');
				++j;
			}
			j = 0;
			putchar('\n');
		}
	}
//	printf("Tab bar chart:\n");
	while (tab != 0) {
		putchar('*');
		--tab;
	}
	putchar('\n');
//	printf("Other bar chart:\n");
	while (other != 0) {
		putchar('*');
		--other;
	}
	return (0);
}
