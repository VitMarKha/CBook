#include <stdio.h>
#include <string.h>

void strncpy2(char *s, char *t, int n);
void strncat2(char *s, char *t, int n);
int strncmp2(char *s, char *t, int n);

int	main(void)
{
	char s1[] = "";
	char s2[] = "Hello\0";
	strncpy2(s1, s2, 3);
	printf("%s\n", s1);
	
	char s3[] = "Hello\0";
	char s4[] = " world\0";
	strncat2(s3, s4, 4);
	printf("%s\n", s3);
	
	char s5[] = "Hello\0";
	char s6[] = " Hel\0";
	printf("%d\n", strncmp2(s5, s6, 1));
	return (0);
}

/* strncmp2: выдает < 0 при s < t, 0 при s == t, > 0 при s > t */
int strncmp2(char *s, char *t, int n)
{
	while (*s++ == *t++ && n != 0)
	{
		--n;
		if (*s == '\0' || n == 0)
			return (0);
	}
	return (*--s - *--t);
}

/* strcat: копирует n количество символов строки t в конец строки s */
void strncat2(char *s, char *t, int n)
{
	while (*s != '\0')
		s++;
	while ((*s++ = *t++) != '\0')
	{
		--n;
		if (n == 0)
			break ;
	}
}

/* strncpy2: копирует n количество символов из строки t в строку s */
void strncpy2(char *s, char *t, int n)
{
	while ((*s++ = *t++) != '\0')
	{
		--n;
		if (n == 0)
			break ;
	}
}
