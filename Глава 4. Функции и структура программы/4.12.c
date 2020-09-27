#include <stdio.h>

#define MAXLINE 1000

void printd(int n);
void itoa(int n, char s[]);

int main(void)
{
	char str[MAXLINE];
	
	printd(-132);
	putchar('\n');
	itoa(123456, str);
	printf("String: %s", str);
	return (0);
}

/* printd: вывод числа n десятичными числами */
void printd(int n)
{
	if (n < 0)
	{
		putchar('-');
		n = -n;
	}
	if (n / 10)
		printd(n / 10);
	putchar(n % 10 + '0');
}

/* itoa: рекурсивная функция преобразующая число в строку */
void itoa(int n, char s[])
{
	static int i;

	if (n < 0)
	{
		n = -n;
		s[i++] = '-';
	}
	if (n / 10)
		itoa(n / 10, s);
	s[i++] = n % 10 + '0';
	s[i] = '\0';
}
