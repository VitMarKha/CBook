#include <stdio.h>

#define MAXLINE 1000
#define TABSIZE 8

int		get_line(char s[], int lim);
void	reverse(char s[]);
void	detab(char to[], char from[]);

int		main(void)
{
	int		len;
	char	line[MAXLINE];
	char	new_line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0)
	{
		if (len > 0)
		{
			detab(new_line, line);
			printf("%s", new_line);
		}
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

void	detab(char to[], char from[])
{
	int		i;
	int		j;
	int		x;
	char	c;

	i = 0;
	j = 0;
	x = 0;
	while ((c = from[i]) != '\0')
	{
		if (c == '\t')
		{
			while (x != TABSIZE)
			{
				to[j] = ' ';
				++j;
				++x;
			}
			x = 0;
		}
		else
		{
			to[j] = c;
			++j;
		}
		++i;
	}
}
