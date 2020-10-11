#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINES 5000 /* максимальное число строк */

char *lineptr[MAXLINES]; /* указатели на строки текста */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reverse);
void quicksort(void *lineptr[], int left, int right,
	 int (*comp)(void *, void *));
int numcmp(char *, char *);
int chcmp(char *, char *);

int directory = 0; /* 1, если сорт. игнорирует пунктуацию */
int case_insensitive = 0; /* 1, если сорт. нечувств. к регистру */
int fs = 0, ff = 0; /* начальная и конечная позиции поля */

 /* сортировка строк */
 int main(int argc, char *argv[])
 {
	 int nlines;        /* количество прочитанных строк */
	 int numeric = 0;   /* 1, если сорт. по числ. знач. */
	 int reverse = 0;   /* 1, если выводить по убыванию */
	 int field = 0; /* 1, если определена начальная позиция поля */
	 int c;

	 while (--argc > 0 && ((c = (*++argv)[0]) == '-' || c == '))
		 if (c == '-')
			 while ((c = *++argv[0]))
				 switch (c) {
				 case 'n':
					 numeric = 1;
					 break;
				 case 'r':
					 reverse = 1;
					 break;
				 case 'f':
					 case_insensitive = 1;
					 break;
				 case 'd':
					 directory = 1;
					 break;
				 default:
					 printf("sort: неверный параметр %c\n", c);
					 argc = 0;
					 break;
				 }
		 else if (c == ') {
			 if (!fs && !field) {
				 fs = atoi(++argv[0]);
				 field = 1;
				 if (fs < 0) {
					 printf("sort: значение позиции должно быть неотрицательным\n");
					 fs = 0;
				 }
			 }
			 else if (!ff) {
				 ff = atoi(++argv[0]);
				 if (ff < fs) {
					 printf("sort: конечная позиция поля должна быть больше начальной\n");
					 ff = 0;
				 }
			 }
		 }
		 else
			 printf("вызов: sort -nrfd +field_start +field_finish\n");

	 if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		 if (numeric)
			 quicksort((void **) lineptr, 0, nlines-1,
					 (int (*)(void *, void *)) numcmp);
		 else
			 quicksort((void **) lineptr, 0, nlines-1,
					 (int (*)(void *, void *)) chcmp);
		 printf("SORTED:\n");
		 writelines(lineptr, nlines, reverse);
		 return 0;
	 } else {
		 printf("Bведено слишком много строк\n");
		 return 1;
	 }
 }

#define MAXLENGTH 80 /* максимальная длина строки */

 void substr(char *, char *);

 /* numcmp: сравнивает s1 и s2 как числа */
 int numcmp(char *s1, char *s2)
 {
	 double v1, v2;
	 char sub[MAXLENGTH];

	 substr(s1, sub);
	 v1 = atof(sub);
	 substr(s2, sub);
	 v2 = atof(sub);
	 if (v1 < v2)
		 return -1;
	 else if (v1 > v2)
		 return 1;
	 else
		 return 0;
 }

 void substr(char *string, char *substring)
 {
	 extern int fs, ff;
	 int i, j, len;

	 len = strlen(string);
	 if (ff > 0 && ff < len)
		 len = ff;
	 else if (ff > 0 && ff > len)
		 printf("sort: слишком короткая строка");
	 for (i = fs, j = 0; i < len; i++, j++)
		 substring[j] = string[i];
	 substring[j] = '\0';
 }

 /* chcmp: сравнивает s1 и s2, игнорируя разницу в регистре и/или
  * символы пунктуации */
 int chcmp(char *s1, char *s2)
 {
	 extern int fs, ff;
	 int i, j, len;

	 i = j = fs;
	 if (ff > 0)
		 len = ff;
	 else if ((len = strlen(s1)) > strlen(s2) )
		 len = strlen(s2);
	 if(directory) {
		 while(i < len && !isdigit(s1[i]) && !isalpha(s1[i]) && !isspace(s1[i]) && s1[i])
			 i++;
		 while(j < len && !isdigit(s2[j]) && !isalpha(s2[j]) && !isspace(s2[j]) && s2[j])
			 j++;
	 }
	 while(i < len && j < len && case_insensitive ? (tolower(s1[i]) == tolower(s2[j])) : (s1[i] == s2[j])) {
		 if(s1[i] == '\0')
			 return 0;
		 i++;
		 j++;
		 if(directory) {
			 while(i < len && !isdigit(s1[i]) && !isalpha(s1[i]) && !isspace(s1[i]) && s1[i])
				 i++;
			 while(j < len && !isdigit(s2[j]) && !isalpha(s2[j]) && !isspace(s2[j]) && s2[j])
				 j++;
		 }
	 }
	 return case_insensitive ? (tolower(s1[i]) - tolower(s2[j])) : (s1[i] - s2[j]);
 }
