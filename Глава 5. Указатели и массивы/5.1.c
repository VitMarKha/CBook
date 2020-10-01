#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int		getch(void);
void	ungetch(int);
int		getint(int *pn);

#define MAXSIZE 10

int	main(void)
{
	int n;
	int array[MAXSIZE];

	n = 0;
	while (n < MAXSIZE && getint(&array[n]) != EOF)
	{
		printf("array[%d] = %d\n", n, array[n]);
		n++;
	}
	return (0);
}

/* getint: считывает очередное целое число из входного потока */
int getint(int *pn)
{
	int c;
	int sign;
	while (isspace(c = getch())); /* пропуск пробелов */
	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
	{
//		ungetch(c); /* не цыфра */
		return (0);
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
	{
		c = getch();
		if (!isdigit(c))
		{
			ungetch((sign == 1) ? '+' : '-');
			return (0);
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return (c);
}

char buf[MAXSIZE]; /* буфер для ungetch */
int bufp = 0; /* следующая свободная позицыя в buf */
				
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= MAXSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
