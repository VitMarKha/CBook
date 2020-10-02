#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);
int strlenf(char *s);

int	main(void)
{
	char s[] = "Hello world\0";
	char t[] = "world\0";
	printf("%d", strend(s, t));
	return (0);
}

/* strend: возвращает 1 если строка t присутствует в конце строки s и 0 в противном случае */
int strend(char *s, char *t)
{
	int i;
	char *tmp;

	i = 0;
	while (*s++ != *t); /* первый схожий элемент */
	s--;
	tmp = t;
	while (*tmp && *s++ == *tmp++)
		++i;
	if (i == strlenf(t))
		return (1);
	return (0);
}

int strlenf(char *s)
{
	int i;

	i = 0;
	while (*s++ != '\0')
		++i;
	return (i);
}
