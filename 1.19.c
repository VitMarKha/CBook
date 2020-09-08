#include <stdio.h>

#define MAXLINE 1000

int		get_line(char s[], int lim);
void	reverse(char s[]);

int		main(void)
{
	int		len;
	char	line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0)
	{
		printf("Reverse: ");
		reverse(line);
		printf("\n");
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

void	reverse(char s[])
{
	int	len;

	len = 0;
	while (s[len] != '\n')
		++len;
	while (len >= 0)
	{
		printf("%c", s[len]);
		--len;
	}
}
