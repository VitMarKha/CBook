#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORLD 100
#define NKEYS 4 //(sizeof(keytab) / sizeof(struct key))

struct key {
	char *word;
	int count;
} keytab[] = {
	{"char", 0},
	{"int", 0},
	{"return", 0},
	{"struct", 0}
};

int getworld(char *word, int lim);
int binsearch(char *word, struct key tab[], int n);

/* подсчет ключевых слов */
int	main(void)
{
	int n;
	char word[MAXWORLD];

	while (getworld(word, MAXWORLD) != EOF)
	{
		if (isalpha(word[0]))
		{
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
		}
	}
	n = 0;
	while (n < NKEYS)
	{
		printf("%s: %d\n", keytab[n].word, keytab[n].count);
		++n;
	}
	return (0);
}

/* binsearch: поиск слова среди tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low;
	int mid;
	int high;

	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return (-1);
}

int getch(void);
void ungetch(int c);

/* getworld: принимает из потока слово */
int getworld(char *word, int lim)
{
	int c;
	int t;
	char *w = word;

	while (isspace(c = getch()));
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c))
	{
		*w = '\0';
		return (c);
	}
	if (isalpha(c))
	{
		while (--lim > 0)
		{
			if (!isalnum(*w = getch()))
			{
				ungetch(*w);
				break ;
			}
			++w;
		}
	}
	else if (c == '"')
		while ((t = getch()) != c && t != EOF);
	*w = '\0';
	return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* буфер для ungetch */
int bufp = 0; /* следующая свободная позицыя в buf */

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
