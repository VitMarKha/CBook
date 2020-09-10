#include <stdio.h>

#define MAXLINE 1000
#define TABSIZE 8
#define TAB '\t'

int		get_line(char s[], int lim);
void	reverse(char s[]);
void	entab(char to[], char from[]);

int		main(void)
{
	int		len;
	char	line[MAXLINE];
	char	new_line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0)
	{
		if (len > 0)
		{
			entab(new_line, line);
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

void	entab(char to[], char from[])
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
			nt = ns / (TABSIZE - 1);
			for (m = 0; m < nt; ++m, ++j)
			{
				to[j] = '\t';
			}
			for (k = 0; k < ns - nt * (TABSIZE - 1) - (nt - 1); ++k, ++j)
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

//void	entab(char to[], char from[])
//{
//	int		i;
//	int		j;
//	int		space;
//	char	c;
//
//	i = 0;
//	j = 0;
//	space = 0;
//	while ((c = from[i]) != '\0')
//	{
//		if (c == ' ')
//		{
//			++space;
//			if (space == TABSIZE)
//			{
//				++j;
//				to[j] = TAB;
//				space = 0;
//			}
//		}
//		else
//		{
//			to[j] = c;
//			++j;
//		}
//		++i;
//	}
//	to[j] = '\0';
//}
