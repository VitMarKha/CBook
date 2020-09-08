#include <stdio.h>

#define MAXLINE 1000

int		get_line(char s[], int lim);
void	reverse(char to[], char from[], int lim);

int		main(void)
{
	int		len;
	char	line[MAXLINE];
	char	line_revers[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0)
	{
		reverse(line_revers, line, len);
		printf("Reverse: %s\n", line_revers);
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

void	reverse(char to[], char from[], int lim)
{
	int	i;
	
	i = 0;
	while (i < (lim - 1))
	{
		to[lim - 2 - i] = from[i];
		++i;
	}
	to[lim - 1] = '\n';
	to[lim] = '\0';
}
