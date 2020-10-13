#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORLD 100

struct thone {
	char *word; /* узел дерева */
	int count; /* частота употребления */
	struct thone *left; /* левый дочерний узел */
	struct thone *right; /* правый дочерний узел */
};

struct thone *addtree(struct thone *p, char *w);
void treeprint(struct thone *p);
int getword(char *word, int lim);

int num;

/* подсчет ключевых слов */
int	main(int argc, char *argv[])
{
	struct thone *root;
	char word[MAXWORLD];

	if (argc == 2)
		num = atoi(argv[1]);
	else if (argc < 2)
		num = 3; /* значение по умолчанию */
	else
	{
		printf("Error: not argument\n");
		exit(-1);
	}
	root = NULL;
	while (getword(word, MAXWORLD) != EOF)
	{
		if (isalpha(word[0]))
			root = addtree(root, word);
	}
	treeprint(root);
	return (0);
}

struct thone *talloc(void);
char *strdup2(char *s);

/* addtree: добавление узла со словом w в узел p или ниже */
struct thone *addtree(struct thone *p, char *w)
{
	int cond;

	if (p == NULL) /* поступило новое слово */
	{
		p = talloc(); /* создается новый узел */
		p->word = strdup2(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strncmp(w, p->word, num)) == 0) /* повторяющее слово */
		p->count++;
	else if (cond < 0) /* меньше левого дерева */
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return (p);
}

/* treeprint: вывод дерева p в алфавитном порядке */
void treeprint(struct thone *p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

/* talloc: создание узла дерева типа thone */
struct thone *talloc(void)
{
	return (struct thone *) malloc(sizeof(struct thone));
}

/* strdup: создает дубликат строки */
char *strdup2(char *s)
{
	char *p;
	
	p = (char *) malloc(sizeof(s) + 1 ); /* +1 для '\0' */
	if (p != NULL)
		strcpy(p, s);
	return (p);
}

int getch(void);
void ungetch(int c);

/* getworld: принимает из потока слово */
int getword(char *word, int lim)
{
	int c;
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
