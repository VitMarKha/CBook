#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int			getch(void);
void		ungetch(int);
double		getfloat(double *pn);

#define MAXSIZE 10

int	main(void)
{
	int n;
	double array[MAXSIZE];

	n = 0;
	while (n < MAXSIZE && getfloat(&array[n]) != EOF)
	{
		printf("array[%d] = %f\n", n, array[n]);
		n++;
	}
	return (0);
}

/* getint: считывает очередное целое число из входного потока */
double getfloat(double *pn)
{
	int c;
	float power;
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
	for (*pn = 0.0; isdigit(c); c = getch())
		*pn = 10.0 * *pn + (c - '0');
	if (c == '.')
		c = getch();
	for (power = 1.0; isdigit(c); c = getch())
	{
		*pn = 10.0 * *pn + (c - '0');
		power *= 10.0;
	}
	*pn *= sign / power;
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
