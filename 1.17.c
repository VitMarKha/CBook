#include <stdio.h>

#define MAXLINE 1000

int		get_line(char s[], int lim);
void	copy(char to[], char from[]);

int		main(void)
{
	int		len;
	int		max;
	char	line[MAXLINE];
	char	longest[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0)
	{
		if (len > max)
		{
			max = len;
			copy(longest, line);
		}
	}
	if (max > 10)
	{
		printf("Max line: %s", longest);
	}
	return (0);
}

int		get_line(char s[], int lim)
{
	int	i;
	int	c;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
	{
		s[i] = c;
	}
	if (c == '\n')
	{
		s[i] = '\n';
		++i;
	}
	s[i] = '\0';
	return (i);
}

void	copy(char to[], char from[])
{
	int	i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
	{
		++i;
	}
}
