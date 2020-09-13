#include <stdio.h>

int	main(void)
{
	int	c;
	int	gaps;
	int	taps;
	int	nls;

	gaps = 0;
	taps = 0;
	nls = 0;
	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
		{
			++nls;
		}
		else if (c == ' ')
		{
			++gaps;
		}
		else if (c == '\t')
		{
			++taps;
		}
	}
	printf("Probels: %d\nTabs %d\nNewLine: %d", gaps, taps, nls);
	return (0);
}
