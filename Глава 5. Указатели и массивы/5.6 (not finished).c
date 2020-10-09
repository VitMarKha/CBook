#include <stdio.h>
#include <string.h>

#include <limits.h>
#include <stdlib.h>

#define MAXLINE 1000

int	get_line(char *s, int lim);

int	main(void)
{
	int len;
	char line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0)
	{
		printf("Len line: %d", len);
	}
	return (0);
}

int	get_line(char *s, int lim)
{
	int	c;
	char *start;

	start = s;
	while (lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return (s-- - start);
}
