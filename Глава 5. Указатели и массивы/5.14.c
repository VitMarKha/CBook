#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000 /* максимальное количество сортируемых строк */
#define MAXLEN 1000
char *lineptr[MAXLINES]; /* указатели на строки */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsortf(char *v[], int left, int right, int (*comp) (void *, void *));
void swap(void *v[], int i, int j);
int	get_line(char s[], int lim);
char *alloc(int);
int numcmp(char *s1, char *s2);

/* сортировка строк входного потока */
int	main(int argc, char *argv[])
{
	char	nlines; /* количество считаных строк */
	int		numeric = 0; /* 1 если числовая сортировка */

	if (argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 1;
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		qsortf((void **) lineptr, 0, nlines - 1,
			   (int (*)(void*, void*)) (numeric ? numcmp : strcmp));
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

/* readlines: считывание строк из входного потока */
int readlines(char *lineptr[], int maxlines)
{
	int len;
	int nlines;
	char *p;
	char line[MAXLEN];

	nlines = 0;
	while ((len = get_line(line, MAXLINES)) > 0)
	{
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
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

/* qsortf: сортировка v[left]...v[right] в порядке возврастания */
void qsortf(char *v[], int left, int right, int (*comp) (void *, void *))
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
		if ((* comp) (v[i], v[left]) < 0)
			swap(v, ++last, i);
		++i;
	}
	swap(v, left, last);
	qsortf(v, left, last - 1, comp);
	qsortf(v, last + 1, right, comp);
}

/* swap: обмен местами v[i] и v[j] */
void swap(void *v[], int i, int j)
{
	void *temp;

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

/* numcmp: сравнение строк s1 и s2 по числовым значениям */
int numcmp(char *s1, char *s2)
{
	double v1;
	double v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return (-1);
	else if (v1 > v2)
		return (1);
	else
		return (0);
}








//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define MAXLINES 5000 /* максимальное количество сортируемых строк */
//#define MAXLEN 1000
//char *lineptr[MAXLINES]; /* указатели на строки */
//
//int readlines(char *lineptr[], int nlines, char *linestore);
//void writelines(char *lineptr[], int nlines);
//void qsortf(char *lineptr[], int left, int right,
//		   int (*comp)(void *, void *));
//int numcmp(char *, char *);
//void swap(void *v[], int i, int j);
//int get_line(char *, int);
//
///* сортировка строк входного потока */
//int	main(int argc, char *argv[])
//{
//	char	nlines; /* количество считаных строк */
//	int		numeric = 0; /* 1 если числовая сортировка */
//
//	if (argc > 1 && strcmp(argv[1], "-n") == 0)
//		numeric = 1;
//	if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
//	{
//		qsortf((void **) lineptr, 0, nlines - 1,
//			   (int (*)(void*, void*)) (numeric ? numcmp : strcmp));
//		writelines(lineptr, nlines);
//		return (0);
//	}
//	else
//	{
//		printf("Error: input too big to sort\n");
//		return (1);
//	}
//	return (0);
//}
//
///* readlines: считывание строк из входного потока */
//int readlines(char *lineptr[], int maxlines, char *linestore)
//{
//	int len;
//	int nlines;
//	char *p;
//	char line[MAXLEN];
//
//	nlines = 0;
//	p = linestore + strlen(linestore);
//	while ((len = get_line(line, MAXLINES)) > 0)
//	{
//		if (nlines >= maxlines || (len + strlen(linestore)) >= ALLOCSIZE)
//			return (-1);
//		else
//		{
//			line[len - 1] = '\0'; /* удаление конца строки */
//			strcpy(p, line);
//			lineptr[nlines++] = p;
//			p += len;
//		}
//	}
//	return (nlines);
//}
//
///* writelines: вывод строк в выходной поток */
//void writelines(char *lineptr[], int nlines)
//{
//	while (nlines-- > 0)
//		printf("%s\n", *lineptr++);
//}
//
///* qsortf: сортировка v[left]...v[right] в порядке возврастания */
//void qsortf(char *v[], int left, int right, int (*comp) (void *, void *))
//{
//	int i;
//	int last;
//
//	if (left >= right)	/* ничего не делать, елси в масиве */
//		return ;		/* меньше двух элементов */
//	swap(v, left, (left + right) / 2);
//	last = left;
//	i = left + 1;
//	while (i <= right)
//	{
//		if ((* comp) (v[i], v[left]) < 0)
//			swap(v, ++last, i);
//		++i;
//	}
//	swap(v, left, last);
//	qsortf(v, left, last - 1, comp);
//	qsortf(v, last + 1, right, comp);
//}
//
///* swap: обмен местами v[i] и v[j] */
//void swap(void *v[], int i, int j)
//{
//	void *temp;
//
//	temp = v[i];
//	v[i] = v[j];
//	v[j] = temp;
//}
//
///* get_line: считывает строку в s возвращает ее длину */
//int		get_line(char s[], int lim)
//{
//	int	i;
//	int	c;
//
//	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
//		s[i] = c;
//	if (c == '\n')
//	{
//		s[i] = '\n';
//		++i;
//	}
//	s[i] = '\0';
//	return (i);
//}
//
///* numcmp: сравнение строк s1 и s2 по числовым значениям */
//int numcmp(char *s1, char *s2)
//{
//	double v1;
//	double v2;
//
//	v1 = atof(s1);
//	v2 = atof(s2);
//	if (v1 < v2)
//		return (-1);
//	else if (v1 > v2)
//		return (1);
//	else
//		return (0);
//}
