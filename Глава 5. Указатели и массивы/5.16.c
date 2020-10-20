#include <stdio.h>
 #include <string.h>
 #include <ctype.h>
 #include <stdlib.h>

 #define MAXLINES 5000 /* максимальное число строк */

 char *lineptr[MAXLINES]; /* указатели на строки текста */

 int readlines(char *lineptr[], int nlines);
 void setlower(char *lineptr[], int nlines);
 void writelines(char *lineptr[], int nlines, int reverse);
 void quicksort(void *lineptr[], int left, int right,
	  int (*comp)(void *, void *));
 int numcmp(char *, char *);

 /* сортировка строк */
 int main(int argc, char *argv[])
 {
	 int nlines;        /* количество прочитанных строк */
	 int numeric = 0;   /* 1, если сорт. по числ. знач. */
	 int reverse = 0;   /* 1, если выводить по убыванию */
	 int directory = 0; /* 1, если сорт. игнорирует пунктуацию */
	 int case_insensetive = 0; /* 1, если сорт. нечувств. к регистру */
	 int c;

	 while (--argc > 0 && (*++argv)[0] == '-')
		 while ((c = *++argv[0]))
		   switch (c) {
		   case 'n':
			 numeric = 1;
			 break;
		   case 'r':
			 reverse = 1;
			 break;
		   case 'f':
			 case_insensetive = 1;
			 break;
		   case 'd':
			   directory = 1;
			   break;
		   default:
			 printf("sort: неверный параметр %c\n", c);
			 argc = 0;
			 break;
		   }

	 if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
			 if (numeric)
				 quicksort((void **) lineptr, 0, nlines-1,
						 (int (*)(void *, void *)) numcmp);
			 else if (case_insensetive)
				 quicksort((void **) lineptr, 0, nlines-1,
						 (int (*)(void *, void *)) chcmp);
			 else
				 quicksort((void **) lineptr, 0, nlines-1,
						 (int (*)(void *, void *)) strcmp);
			 printf("SORTED:\n");
			 writelines(lineptr, nlines, reverse);
			 return 0;
		 } else {
			 printf("Bведено слишком много строк\n");
			 return 1;
		 }
 }

 /* setlower: преобразование символов к нижнему регистру */
 void setlower(char *lineptr[], int nlines)
 {
	 int i, j;

	 for (i=0; i < nlines; i++) {
		 j = 0;
		 while(lineptr[i][j]) {
			 lineptr[i][j] = tolower(lineptr[i][j]);
			 j++;
		 }
	 }
 }

/* chcmp: сравнивает s1 и s2, игнорируя разницу в регистре и/или
  * символы пунктуации */
 int chcmp(char *s1, char *s2)
 {
	 if(directory) {
		 while(!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1)
			 ++s1;
		 while(!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2)
			 ++s2;
	 }
	 while(case_insensetive ? (tolower(*s1) == tolower(*s2)) : (*s1 == *s2)) {
		 if(*s1 == '\0')
			 return 0;
		 ++s1;
		 ++s2;
		 if(directory) {
			 while(!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1)
				 ++s1;
			 while(!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2)
				 ++s2;
		 }
	 }
	 return case_insensetive ? (tolower(*s1) - tolower(*s2)) : (*s1 - *s2);
 }
