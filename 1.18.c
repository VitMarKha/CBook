#include <stdio.h>

#define MAXLINE 1000

int		get_line(char s[], int lim);
void	copy(char to[], char from[]);
void	delet_spaces(char to[], char from[], int max);

int		main(void)
{
	int		len;
	int		max;
	char	line[MAXLINE];
	char	longest[MAXLINE];
	char	array_without_spaces[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0)
	{
		--len;
		--len;
		while (line[len] == ' ' || line[len] == '\t')
			--len;
		if (len > max)
		{
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0)
	{
		delet_spaces(array_without_spaces, longest, max);
		printf("Max line without spaces: %s", array_without_spaces);
	}
	return (0);
}

int		get_line(char s[], int lim)
{
	int i;
	int c;

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
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
	{
		++i;
	}
}

void	delet_spaces(char to[], char from[], int max)
{
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
	{
		if (i == max)
		{
			break ;
		}
		++i;
	}
}
