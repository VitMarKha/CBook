#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAXLINE 1000

int	strlenf(char s[]);
int	strindex_right(char s[], char t[]);
int	get_line(char s[], int lim);

char patern[] = "outs";

int	main(void)
{
	char line[MAXLINE];
	int found = 0;
	
	while (get_line(line, MAXLINE) > 0)
	{
		if (strindex_right(line, patern) >= 0)
		{
			printf("String: %s", line);
			++found;
		}
	}
	printf("Found in %d lines",found);
	return found;
}
/* strindex_right: возвращает самый правый индекс вхождения строки t в строке s, или -1 если вхождения нет */
int	strindex_right(char s[], char t[])
{
	int i;
	int j;
	int len;
	int len_patern;
	
	i = 0;
	len = strlenf(s);
	len_patern = strlenf(t);
	printf("Len str: %d\n",len);
	printf("len patern: %d\n",len_patern);
	while (len >= 0)
	{
		if (s[len] == t[len_patern])
		{
			j = len;
			while (s[j--] == t[len_patern--])
			{
				if (s[j] == t[0])
				{
					printf("Right occurrence index: %d\n", j);
					return (j);
				}
			}
		}
		--len;
	}
	return (-1);
}

int	get_line(char s[], int lim)
{
	int	i;
	int	c;

	i = 0;
	while (lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return (i);
}

int strlenf(char s[])
{
	int i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}
