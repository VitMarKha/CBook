#include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

 #define MAXLINE 1000

 int except = 0, number = 0, found = 0;

 void finder(char *, FILE *, int);

 /* find: поиск строк по образцу из командной строки */
 int main(int argc, char *argv[])
 {
	char *pattern, *prog = argv[0];
	FILE *inp;
	 int c;

	while (--argc > 0 && (*++argv)[0] == '-')
		while ((c = *++argv[0]))
		  switch (c) {
		  case 'x':
			except = 1;
			break;
		  case 'n':
			number = 1;
			break;
		  default:
			fprintf(stderr, "find: неверный параметр %c\n", c);
			argc = 0;
			found = -1;
			break;
		  }
	if (argc < 1) {
		fprintf(stderr, "usage: find -x -n pattern\n");
		exit(1);
	}
	pattern = *argv;
	if (!--argc) {
		finder(pattern, stdin, MAXLINE);
		exit(0);
	}
	while (argc-- && (inp = fopen(*++argv, "r")) != NULL) {
		 finder(pattern, inp, MAXLINE);
	}
	if (!argc) {
		fprintf(stderr, "%s: can't open %s\n", prog, *argv);
		exit(1);
	}
	return found;
 }

 /* finder: поиск по образцу pattern в файле input */
 void finder(char *pattern, FILE *input, int maxline) {
	long lineno = 0;
	char line[MAXLINE], *p;

	while ((p = fgets(line, maxline, input)) != NULL) {
		lineno++;
		if ((strstr(line, pattern) != NULL) != except) {
			if (number)
				printf("%ld:", lineno);
			printf("%s", line);
			found++;
		}
	}
 }
