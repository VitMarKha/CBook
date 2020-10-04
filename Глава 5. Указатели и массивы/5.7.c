#include <stdio.h>
#include <string.h>

#define MAXLINE 5000 /* максимальное количество сортируемыз строк */
#define ALLOCSIZE 10000

char *lineptr[MAXLINE]; /* указатели на строки */

int readlines(char *lineptr[], int nlines, char *linestore);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

/* сортировка строк входного потока */
int	main(void)
{
	char allocbuf[ALLOCSIZE]; /* массив для хранения строк */
	int nlines; /* количество введеных строк */
	
	if ((nlines = readlines(lineptr, MAXLINE, allocbuf)) >= 0)
	{
//		qsort(lineptr, 0, nlines - 1);
		printf("nlines = %d\n", nlines);
		writelines(lineptr, nlines);
		return (0);
	}
	else
	{
		printf("Error: input too big to sort\n");
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
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

void swap(char *v[], int i, int j);

/* qsort: сортировка v[left]...v[right] в порядке возврастания */
void qsort(char *v[], int left, int right)
{
	int i;
	int last;
	
	if (left >= right)	/* ничего не делать, елси в масиве */
		return ;		/* меньше двух элементов */
	swap(v, left, (left + right) / 2);
	last = left;
	i = left + 1;
	while (i <= right)
	{
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

/* swap: обмен местами v[i] и v[j] */
void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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
