#include <stdio.h>

#define MAXLINE 1000
#define STRLEN 10
#define NEWLINE '\n'

int		get_line(char s[], int lim);
void	separator(char to[], char from[]);

int		main(void)
{
	int		len;
	char	line[MAXLINE];
	char	new_line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0)
	{
		if (len > 0)
		{
			separator(new_line, line);
			printf("%s", new_line);
		}
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

void	separator(char to[], char from[])
{
	int i;
	int x;
	int tmp;

	i = 0;
	x = 0;
	while (from[i] != EOF)
	{
		if (x == STRLEN)
		{
			if (from[i] == ' ')
			{
				to[i] = NEWLINE;
				x = 0;
			}
			else
			{
				tmp = i;
				while (1)
				{
					if (from[i] == ' ')
					{
						from[i] = NEWLINE;
						to[i] = from[i];
						break ;
					}
					else if (i == 0)
					{
						i = tmp;
						to[i] = from[i];
						break ;
					}
					--i;
				}
			}
		}
		else
		{
			to[i] = from[i];
		}
		++x;
		++i;
	}
	to[i] = '\0';
}
