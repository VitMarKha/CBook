#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* Для объявления atoi() */

#define MAXLINE 5000 /* максимальное количество сортируемых строк */
#define ALLOCSIZE 10000

char *lineptr[MAXLINE]; /* указатели на строки */

int readlines(char *lineptr[], int nlines, char *linestore);
void writelines(char *lineptr[], int nlines, int n);

/* сортировка строк входного потока */
int	main(int argc, char *argv[])
{
	char allocbuf[ALLOCSIZE]; /* массив для хранения строк */
	int nlines; /* количество введеных строк */

	if (argc != 1 && (*++argv)[0] == '-')
	{
		if ((nlines = readlines(lineptr, MAXLINE, allocbuf)) >= 0)
		{
			printf("nlines = %d\n", nlines);
			writelines(lineptr, nlines, atoi(*argv) * -1);
			return (0);
		}
	}
	else
	{
		printf("Error: not comand\n");
		return (1);
	}
	return (0);
}

#define MAXLEN 1000
int get_line(char *, int);

/* readlines: считывание строк из входного потока */
int readlines(char *lineptr[], int maxlines, char *linestore)
{
	int len;
	int nlines;
	char *p;
	char line[MAXLEN];
	
	nlines = 0;
	p = linestore + strlen(linestore);
	while ((len = get_line(line, MAXLINE)) > 0)
	{
		if (nlines >= maxlines || (len + strlen(linestore)) >= ALLOCSIZE)
			return (-1);
		else
		{
			line[len - 1] = '\0'; /* удаление конца строки */
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;
		}
	}
	return (nlines);
}

/* writelines: вывод строк в выходной поток */
void writelines(char *lineptr[], int nlines, int n)
{
	int i;
	char *mass[MAXLINE];

	i = 0;
	while (nlines-- > 0)
	{
		mass[i] = *lineptr++;
		++i;
	}
	--i;
	while (n-- > 0)
		printf("%s\n", mass[i--]);
}

/* get_line: считывает строку в s возвращает ее длину */
int		get_line(char s[], int lim)
{
	int	i;
	int	c;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
	{
		s[i] = '\n';
		++i;
	}
	s[i] = '\0';
	return (i);
}
