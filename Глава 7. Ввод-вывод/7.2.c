#include <stdio.h>
#include <ctype.h>

#define MAXLEN 30

int	main(void)
{
	char c;
	int n;

	n = 0;
	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
		{
			putchar('\n');
			n = 0;
		}
		else if (c != '\n' && !isprint(c))
		{
			if (n > MAXLEN)
			{
				putchar('\n');
				n = 0;
			}
			printf("%x", c);
			++n;
		}
		else
		{
			if (n > MAXLEN)
			{
				putchar('\n');
				n = 0;
			}
			putchar(c);
			++n;
		}
	}
	return (0);
}
