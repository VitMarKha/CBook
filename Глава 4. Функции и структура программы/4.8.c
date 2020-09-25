#include <stdio.h>

void ungetch(int c);
int getch(void);

/* Возвращает назад 1 символ */
int main(void)
{
	int c;

	while ((c = getch()) != EOF)
	{
		if (c == 'f')
		{
			ungetch('F');
			putchar(getch());
		}
		else
			putchar(c);
	}
	return (0);
}

int buf = 0; /* переменная-буфер */

int getch(void) /* взять символ */
{
	int t;

	if (buf != 0)
	{
		t = buf;
		buf = 0;
	}
	else
		t = getchar();
	return t;
}

void ungetch(int c) /* вернуть символ на ввод */
{
	if (buf == 0)
		buf = c;
	else
		printf("ungetch: too many characters\n");
}
