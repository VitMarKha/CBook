#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100

/* filecmp: сравнение содержимого двух файлов */
int main(int argc, char *argv[])
{
	int i = 0;
	FILE *fp1, *fp2;
	char *s1;
	char *s2;
	char line1[MAXLINE];
	char line2[MAXLINE];
	char *prog = argv[0]; /* имя программы */

	if (argc != 3)
	{
		fprintf(stderr, "usage: filecmp file1 file2\n");
		exit(1);
	}
	if ((fp1 = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "%s: can't open file %s\n", prog, argv[1]);
		exit(1);
	}
	if ((fp2 = fopen(argv[2], "r")) == NULL)
	{
		fprintf(stderr, "%s: can't open file %s\n", prog, argv[2]);
		exit(1);
	}
	if (!strcmp(argv[1], argv[2]))
	{ /* не одинаковы ли файлы? */
		printf("no differences\n");
		exit(0);
	}
	while ((s1 = fgets(line1, MAXLINE, fp1)) != NULL &&
		   (s2 = fgets(line2, MAXLINE, fp2)) != NULL)
	{
		i++;
		if (strcmp(line1, line2))
		{
			printf("\ndifference:\n");
			printf("line %d in %s: %s", i, argv[1], s1);
			printf("line %d in %s: %s", i, argv[2], s2);
			exit(0);
		}
	}
	/* если один из файлов закончился раньше другого */
	if (s1 && !s2)
	{
		printf("\ndifference:\n");
		printf("line %d in %s: %s", i, argv[1], s1);
		printf("EOF in %s\n", argv[2]);
	}
	else if (!s1 && s2)
	{
		printf("\ndifference:\n");
		printf("EOF in %s\n", argv[1]);
		printf("line %d in %s: %s", i, argv[2], s2);
	}
	else
		printf("no differences\n");
	exit(0);
}
