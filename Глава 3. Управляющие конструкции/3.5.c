#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAXLINE 1000

void	itoa(int n, char s[]);
void	itob(int n, char s[], int b);
void	reverse(char s[]);
int		strlenf(char s[]);

int	main(void)
{
	char s[MAXLINE];
	int hex = 16;
	itob(123342314, s, hex);
	printf("String in hex: %s\n", s);
	return 0;
}
/* itob: преобразование n в строку s, представляющую число по основанию b (2 <= b <= 16) */
void itob(int n, char s[], int b)
{
	int i;
	int sign;
	char digits[] = "0123456789ABCDEF";

	sign = n;
	i = 0;
	do /* генерируем цифры в обратном порядке */
	{
		s[i++] = digits[n % b];    /* следующая цифра */
	}
	while (n /= b);  /* исключить ее */
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
