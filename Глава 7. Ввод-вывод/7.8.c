#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define PAGELEN 15


void fprinter(FILE *, int);

/* fileprint: печать файлов, имена которых заданы в командной строке */
int main(int argc, char *argv[])
{
   char *prog = argv[0];
   FILE *inp;

   if (argc == 1) {
	   fprintf(stderr, "usage: fileprint file1, file2, ...\n");
	   exit(1);
   }
   while (--argc) {
	   if ((inp = fopen(*++argv, "r")) != NULL) {
		   printf("-------- begin of file %s --------\n", *argv);
		   fprinter(inp, MAXLINE);
		   printf("--------- end of file %s ---------\n", *argv);
	   }
	   else {
		   fprintf(stderr, "%s: can't open %s\n", prog, *argv);
		   exit(1);
	   }
   }
   return 0;
}

/* fprinter: печать файла input */
void fprinter(FILE *input, int maxline) {
   long t, lineno = 0;
   int pageno = 1;
   char line[MAXLINE], *p;

   printf("-%d-\n", pageno);
   while ((p = fgets(line, maxline, input)) != NULL) {
	   if (lineno++ < PAGELEN)
		   printf("%s", line);
	   else {
		   lineno = 0;
		   printf("-%d-\n", ++pageno);
	   }
   }
   if ((t = PAGELEN - lineno) > 0)
	   while (--t)
		   printf("\n");
}
