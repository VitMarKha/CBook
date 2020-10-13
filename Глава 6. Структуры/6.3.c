#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXLINK 5

struct tnode {           /* узел дерева */
	char *word;           /* указатель на текст */
	int nline[MAXLINK];   /* массив номеров строк */
	int count;            /* индекс в nline[] */
	struct tnode *left;  /* левый дочерний узел */
	struct tnode *right; /* правый дочерний узел */
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int strlenf(char *s);
struct tnode *talloc(void);
char *strdup2(char *s);
int getch(void);
void ungetch(int c);

int num;                  /* Максимальная длина "шумового" слова */
int lnum = 0;             /* Инициализация счетчика строк */

int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];

	if (argc == 2)
		num = atoi(argv[1]);
	else if (argc < 2)
		num = 2;
	else {
		printf("usage: linktree <number>\n");
		exit(-1);
	}

	root = NULL;
	while (getword (word, MAXWORD) != EOF)
		if (isalpha(word[0]) && strlenf(word) > num)
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

/* addtree: добавляет узел со словом w в р или ниже него */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {  /* слово встречается впервые */
		p = talloc(); /* создается новый узел */
		p->word = strdup2(w);
		p->nline[p->count] = lnum;
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->nline[p->count++] = lnum; /* это слово уже встречалось */
	}
	else if (cond < 0)        /* меньше корня левого поддерева */
		p->left = addtree(p->left, w);
	else                      /* больше корня правого поддерева */
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint: упорядоченная печать дерева р */
void treeprint(struct tnode *p)
{
	int i;

	if (p != NULL) {
		treeprint (p->left);
		printf("\n%s ", p->word);
		for (i = 0; i < MAXLINK; i++)
			printf("%2d ",p->nline[i]);
		treeprint(p->right);
	}
}

/* getword: принимает следующее слово или символ из ввода */
int getword (char *word, int lim)
{
	int c, t, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()) && c != '\n');
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == '_') {
		for ( ; --lim > 0; w++) {
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
			else if (*w == '\n') {
				lnum++;
				ungetch(*w);
				break;
			}
		}
	}
	else if (c == '"') {
		while ((t = getch()) != c && t != EOF);
	}
	else if (c == '/') {
		if ((t = getch()) == '*') {
			while ((t = getch()) != EOF )
				if (t == '*') {
					if ((t = getch()) == '/')
						break;
					else
						ungetch(t);
				}
		}
		else
			ungetch(t);
	}
	else if (c == '\n')
		lnum++;
	*w = '\0';
	return c;
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

int strlenf(char *s)
{
	int i;

	i = 0;
	while (*s++ != '\0')
		++i;
	return (i);
}

/* talloc: создание узла дерева типа thone */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
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
