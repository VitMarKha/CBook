#include <stdio.h>

#define BUFSIZE 1000

int		get_line(char s[], int lim);
void	checker(char code[]);

int		main(void)
{
	int		len;
	char	buffer[BUFSIZE];

	len = 0;
	while ((len = get_line(buffer, BUFSIZE)) > 0)
	{
		checker(buffer);
	}
	return 0;
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

void	checker(char code[])
{
	int		i;
	int		c;
	int		nb;
	int		dqf;
	int		cf;
	char	prev;

	i = 0;
	nb = 0;
	dqf = 0;
	cf = 0;
	while ((c = code[i]) != '\0')
	{
		printf("%c", c);
		if (c == '"' && dqf == 0 && cf == 0)
		{
			++dqf;
			printf("<%d", dqf);
		}
		else if (c == '"' && dqf > 0 && prev != '*' && cf == 0)
		{
			--dqf;
			printf("%d>", dqf);
		}
		else if (c == '*' && prev == '/' && dqf == 0)
			++cf;
		else if (c == '/' && prev == '*' && dqf == 0)
			--cf;
		if (c == '(' && dqf == 0 && cf == 0)
		{
			++nb;
			printf("-%d-", nb);
		}
		if (c == ')' && dqf == 0 && cf == 0)
		{
			--nb;
			printf("-%d-", nb);
		}
		prev = c;
		++i;
	}
	if (nb > 0)
		printf("\nНезакрытых ')': %d", nb);
	else if (nb < 0)
		printf("\nНезакрытых '(': %d", -nb);
	else
		printf("\nOK");
}
