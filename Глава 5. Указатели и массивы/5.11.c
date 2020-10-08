#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define TABSIZE 4

int		get_line(char s[], int lim);
void	reverse(char s[]);
void	detab(char to[], char from[], int size);
void	entab(char to[], char from[], int size);


int		main(int argc, char *argv[])
{
	int		len;
	char	line[MAXLINE];
	char	new_line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0)
	{
		if (len > 0)
		{
			argc == 1 ? detab(new_line, line, TABSIZE) :
			detab(new_line, line, atoi(argv[1]));
			printf("Detab string: %s", new_line);
			argc == 1 ? entab(new_line, line, TABSIZE) :
			entab(new_line, line, atoi(argv[1]));
			printf("Entab string: %s", new_line);
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

void	detab(char to[], char from[], int size)
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
			while (x != size)
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

void	entab(char to[], char from[], int size)
{
	int	i;
	int j;
	int k;
	int ns;
	int nt;
	int c;
	int m;

	i = 0;
	j = 0;
	ns = 0;
	nt = 0;
	while ((c = from[i]) != '\0')
	{
		if (c == ' ')
			++ns;
		else if (ns > 0)
		{
			nt = ns / (size - 1);
			for (m = 0; m < nt; ++m, ++j)
			{
				to[j] = '\t';
			}
			for (k = 0; k < ns - nt * (size - 1) - (nt - 1); ++k, ++j)
			{
				to[j] = ' ';
			}
			to[j] = c;
			ns = 0;
			++j;
		}
		else
		{
			to[j] = c;
			++j;
		}
		++i;
	}
	to[j] = '\0';
}
