#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAXLINE 1000

void	itoa(int n, char s[]);
void	new_itoa(int n, char s[], int c);
void	reverse(char s[]);
int		strlenf(char s[]);
void	probel_in_str(char s[], int n);

int	main(void)
{
	char s[MAXLINE];
	new_itoa(123456, s, 4);
	printf("String with probels:%s\n", s);
	return 0;
}

/* probel_in_str: добавляет пробелы в начало строки */
void probel_in_str(char s[], int n)
{
	int i;
	int j;
	char tmp[MAXLINE];

	i = 0;
	j = 0;
	while (n-- > 0)
		tmp[i++] = ' ';
	while (s[j] != '\0')
		tmp[i++] = s[j++];
	tmp[i] = '\0';
	i = 0;
	while (tmp[i] != '\0')
	{
		s[i] = tmp[i];
		++i;
	}
	s[i] = '\0';
}

/* new_itoa: преобразует число n в строку символов в том числе INT_MIN */
void new_itoa(int n, char s[], int c)
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
	probel_in_str(s, c);
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
