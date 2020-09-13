#include <stdio.h>

#define MAXLINE 1000

int		get_line(char s[], int lim);
void	delet_coment(char to[], char from[]);

int		main(void)
{
	int		len;
	char	line[MAXLINE];
	char	new_line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0)
	{
		if (len > 0)
		{
			delet_coment(new_line, line);
			printf("%s", new_line);
		}
	}
	return (0);
}

int		get_line(char s[], int lim)
{
	int i;
	int c;

	for (i = 0; i < lim && (c = getchar()) != EOF; ++i)
	{
		s[i] = c;
	}
	s[i] = '\0';
	return (i);
}

void	delet_coment(char to[], char from[])
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = 0;
	while (from[i] != EOF)
	{
		if (from[i] == '/' && from[i + 1] == '*' && flag == 0)
		{
			flag = 1;
			++i;
		}
		else if (from[i] == '*' && from[i + 1] == '/' && flag == 1)
		{
			flag = 0;
			++i;
		}
		else if (flag == 0)
		{
			to[j] = from[i];
			++j;
		}
		++i;
	}
	to[i] = '\0';
}
