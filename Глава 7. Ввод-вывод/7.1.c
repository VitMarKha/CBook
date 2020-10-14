#include <stdio.h>

char my_tolower(char c);
int isup(char c);

int	main(int argc, char *argv[])
{
	int c;
	(void)argc;

	while ((c = getchar()) != EOF)
	{
		if (isup(argv[0][2]))
			putchar(my_tolower(c));
		else
			putchar(c);
	}
	return (0);
}

char my_tolower(char c)
{
	if (isup(c))
		c += 32;
	else
		return (c);
	return (c);
}

int isup(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}
