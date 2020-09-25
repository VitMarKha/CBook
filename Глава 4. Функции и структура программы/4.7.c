#include <stdio.h>

int strlenf(char s[]);
void ungets(char s[]);
void ungetch(int c);
int getch(void);

/* Возврат в поток */
int main(void)
{
	char c;
	char str[] = "Hello\nman\n";

	ungets(str);

	while ((c = getch()) != EOF )
		putchar(c);
	return (0);
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* буфер для ungetch */
int bufp = 0; /* следующая свободная позицыя в buf */
				
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void ungets(char s[])
{
	int i = strlenf(s);

	while (i >= 0)
	{
		ungetch(s[--i]);
	}
}

int strlenf(char s[])
{
	int i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}
