#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAXLINE 1000

void itoa(int n, char s[]);
void new_itoa(int n, char s[]);
void reverse(char s[]);
int strlenf(char s[]);

int	main(void)
{
	char s[MAXLINE];
	new_itoa(INT_MIN, s);
	printf("String: %s\n", s);
	return 0;
}
/* new_itoa: преобразует число n в строку символов в том числе INT_MIN */
void new_itoa(int n, char s[])
{
	int i;
	int sign;
	
	sign = n;
	i = 0;
	do /* генерируем цифры в обратном порядке */
	{
		s[i++] = abs(n % 10) + '0';    /* следующая цифра */
	}
	while (n /= 10);  /* исключить ее */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* itoa: преобразует число n в строку символов */
void itoa(int n, char s[])
{
	int i, sign;
	if ((sign = n) < 0) /* сохраняем знак */
		n =-n;          /* делаем n положительным */
	i = 0;
	do /* генерируем цифры в обратном порядке */
	{
		s[i++] = n % 10 + '0';    /* следующая цифра */
	}
	while ((n /= 10) > 0);  /* исключить ее */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void reverse(char s[])
{
	int c;
	int i;
	int j;

	i = 0;
	j = strlenf(s) - 1;
	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
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
