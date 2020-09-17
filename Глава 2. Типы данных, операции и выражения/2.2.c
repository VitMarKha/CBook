#include <stdio.h>

#define MAXLINE 1000

int	get_line(char s[], int lim);

int	main(void)
{
	int		len;
	char	line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0)
	{
		printf("String: %s\n", line);
	}
	return (0);
}

int	get_line(char s[], int lim)
{
	int	i;
	int	c;

	i = 0;
	while (i < lim - 1)
	{
		if ((c = getchar()) != EOF)
		{
			if (c != '\n')
				s[i++] = c;
		}
		else
			break ;
	}
	if (c == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return (i);
}
