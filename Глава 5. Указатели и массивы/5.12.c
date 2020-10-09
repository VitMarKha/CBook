#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 72   /* максимальный размер строки табуляций */
#define TABSIZE 8    /* размер табуляции в пробелах */

void detab(int []);
void settabs(int, char *[], int *);
int tabpos(int col, int tabstops[]);
void entab(int tabstops[]);

int main(int argc, char *argv[])
{
	int tabstops[MAXLINE];

	settabs(argc, argv, tabstops);
	detab(tabstops);
	
	int tabstops2[MAXLINE];

	settabs(argc, argv, tabstops2);
	entab(tabstops2);

	return 0;
}

 /* detab: преобразует символы табуляции из 'from' в пробелы 'to' */
void detab(int tabstops[])
 {
	 int col = 0;
	 char c;

	 while ((c = getchar()) != EOF) {
		 if (c == '\t') {
			 do
				 putchar(' ');
			 while (!tabpos(++col, tabstops));
		 }
		 else if (c == '\n') {
			 putchar(c);
			 col = 0;
		 }
		 else {
			 putchar(c);
			 ++col;
		 }
	 }
 }

void settabs(int argc, char *argv[], int tabstops[])
{
	int i, col;

	if (argc == 1)
		for (i=0; i < MAXLINE; i++)
			tabstops[i] = (i % TABSIZE == 0);
	else {
		for (i=0; i < MAXLINE; i++)
			tabstops[i] = 0;
		while (--argc > 0) {
			col = atoi(*++argv);
			if (col < MAXLINE)
				tabstops[col] = 1;
		}
	}
}

 int tabpos(int col, int tabstops[])
 {
	 if (col > MAXLINE)
		 return 1;
	 else
		 return tabstops[col];
 }

void entab(int tabstops[])
{
	int col = 0, newcol;
	char c;

	do {
		newcol = col;
		while ((c = getchar()) == ' ') {
			newcol++;
			if (tabpos(newcol, tabstops)) {
				putchar('\t');
				col = newcol;
			}
		}
		while (col < newcol) {
			putchar(' ');
			col++;
		}
		if (c != EOF) {
			putchar(c);
			if (c == '\n') {
				col = 0;
			}
			else {
				col++;
			}
		}
	} while (c != EOF);
}
