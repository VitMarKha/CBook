#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define HASHSIZE 101

struct nlist {           /* элемент таблицы */
	struct nlist *next;  /* указатель на следующий элемент */
	char *name;         /* определенное имя */
	char *defn;         /* замещающий текст */
};

static struct nlist *hashtab[HASHSIZE]; /* таблица указателей */

struct nlist *install(char *, char *);
struct nlist *lookup(char *);
unsigned hash(char *);
int getword(char *, int);
int getch(void);
void ungetch(int c);
struct nlist *talloc(void);
char *strdup2(char *s);
void tableprint(void);
void undef(char *s);

int main(void)
 {
	char word[MAXWORD], tword[MAXWORD];
	struct nlist *np;

	while (getword (word, MAXWORD) != EOF) {
		if (strcmp(word, "#") == 0) {
			printf("<directive?>");
			printf("[%s]", word);
			getword (word, MAXWORD);
			if (strcmp(word, "define") == 0) {
				printf("<define>");
				if (isupper(getword (word, MAXWORD))) {
					printf("<NAME>");
					strcpy(tword, word);
					if (isalnum(getword (word, MAXWORD))) {
						printf("<<defn>>");
						np = install(tword, word);
					}
					else
						printf("error: incorrect definition.\n");
				}
				else {
					printf("error: must be only UPPER LETTERS in directive.\n");
				}
			}
			else if (strcmp(word, "undef") == 0) {
				printf("<undef>");
				if (isupper(getword (word, MAXWORD))) {
					printf("<NAME>");
					undef(word);
				}
			}
			else {
				printf("<not>");
			}
		}
		else if ((np = lookup(word)) != NULL) {
			printf("<in table>");
			strcpy(word, np->defn);
		}
		printf("[%s]", word);
	}
	printf("\n");
	tableprint();

	return 0;
 }

 /* install: заносит имя и текст (name, defn) в таблицу */
 struct nlist *install(char *name, char *defn)
 {
	 struct nlist *np;
	 unsigned hashval;

	 if ((np = lookup(name)) == NULL) { /* не найден */
		 np = (struct nlist *) malloc(sizeof(*np));
		 if (np == NULL || (np->name = strdup2(name)) == NULL)
			 return NULL;
		 hashval = hash(name);
		 np->next = hashtab[hashval];
		 hashtab[hashval] = np;
	 } else /* уже имеется */
		 free((void *) np->defn); /* освобождаем прежний defn */
	 if ((np->defn = strdup2(defn)) == NULL)
		 return NULL;
	 return np;
 }

 /* lookup: ищет s */
 struct nlist *lookup(char *s)
 {
	 struct nlist *np;

	 for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		 if (strcmp(s, np->name) == 0)
			 return np; /* нашли */
	 return NULL; /* не нашли */
 }

 /* hash: получает хэш-код для строки s */
 unsigned hash(char *s)
 {
	 unsigned hashval;

	 for (hashval = 0; *s != '\0'; s++)
		 hashval = *s + 31 * hashval;
	 return hashval % HASHSIZE;
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
struct nlist *talloc(void)
{
	return (struct nlist *) malloc(sizeof(struct nlist));
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

void tableprint(void)
{
   int i;
   struct nlist *np;

   for (i=0; i < HASHSIZE; i++)
	   for (np = hashtab[i]; np != NULL; np = np->next)
		   printf("name=%s, defn=%s\n", np->name, np->defn);
}

/* undef: удаление записи из хэш-таблицы hashtab */
 void undef(char *s)
 {
	int i;
	struct nlist *np, *prev;

	prev = NULL;
	i = hash(s);
	for (np = hashtab[i]; np != NULL; np = np->next) {
		if (strcmp(s, np->name) == 0)
			break;
		prev = np;
	}
	if (np != NULL) {
		if (prev == NULL)
			hashtab[i] = np->next;
		else
			prev->next = np->next;
		free((void *) np->name);
		free((void *) np->defn);
		free((void *) np);
	}
 }
