#include <stdio.h>
 #include <ctype.h>
 #include <string.h>
 #include <stdlib.h>

 #define MAXWORD 100
 #define MAXWORDS 20

 struct tnode {           /* узел дерева */
	 char *word;           /* указатель на текст */
	 int count;            /* число вхождений */
	 struct tnode *left;  /* левый дочерний узел */
	 struct tnode *right; /* правый дочерний узел */
 };

struct tnode *addtree(struct tnode *, char *);
void tree2array(struct tnode *);
void bubble_sort(struct tnode *[], int);
void arrayprint(struct tnode *[]);
int getword(char *, int);
void swap(struct tnode *w[], int i, int j);
int getch(void);
void ungetch(int c);
struct tnode *talloc(void);
char *strdup2(char *s);

 struct tnode *words[MAXWORDS];
 int nword = 0;

 int main(void)
 {
	 struct tnode *root;
	 char word[MAXWORD];

	 root = NULL;
	 while (getword (word, MAXWORD) != EOF)
		 if (isalpha(word[0]))
			 root = addtree(root, word);
	 tree2array(root);
	 printf("number of words = %d\n\n", nword);
	 bubble_sort(words, nword);
	 arrayprint(words);
	 return 0;
 }

/* addtree: добавление узла со словом w в узел p или ниже */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) /* поступило новое слово */
	{
		p = talloc(); /* создается новый узел */
		p->word = strdup2(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0) /* повторяющее слово */
		p->count++;
	else if (cond < 0) /* меньше левого дерева */
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return (p);
}

 /* tree2array: сохранение упорядоченного по алфавиту дерева в массиве */
 void tree2array(struct tnode *p)
 {
	 if (p != NULL) {
		 tree2array (p->left);
		 if (nword < MAXWORDS)
			 words[nword++] = p;
		 tree2array(p->right);
	 }
 }

 /* bubble_sort: сортировка *w[] пузырьком */
 void bubble_sort(struct tnode *w[], int n) {
	 int j, t = 1;

	 while (n-- && t)
		 for (j = t = 0; j < n; j++) {
			 if (w[j]->count >= w[j+1]->count) continue;
			 swap(w, j, j+1);
			 t = 1;
		 }
 }

 /* arrayprint: печать массива структур */
 void arrayprint(struct tnode *w[])
 {
	 int i;

	 for (i = 0; i < nword; i++)
		 printf("%4d %s\n", w[i]->count, w[i]->word);
 }

/* swap: поменять местами w[i] и w[j] */
void swap(struct tnode *w[], int i, int j)
{
	struct tnode *temp;

	temp = w[i];
	w[i] = w[j];
	w[j] = temp;
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
