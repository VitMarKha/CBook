#include <stdio.h>
#include <stdarg.h>

#define MAXLEN 10

void minscanf(char *, ...);

int main(void)
{
	int in;
	double db;
	char str[MAXLEN];

	printf("Input int, double, string: ");
	minscanf("%d %f %s", &in, &db, str);
	printf("Output: %d, %lf, %s", in, db, str);
	return 0;
}

/* minscanf: минимальный scanf с переменным числом аргументов */
void minscanf(char *fmt, ...)
{
	va_list ap;        /* указатель на очередной безымянный аргумент */
	char *p, *sval;
	int *ival;
	double *dval;

	va_start(ap, fmt); /* устанавливает ap на 1-й безымянный аргумент */
	for (p=fmt; *p; p++) {
		if (*p =='%') {
			switch (*++p) {
			case 'd':
				ival = va_arg(ap, int *);
				scanf ("%d", ival);
				break;
			case 'f':
				dval = va_arg(ap, double *);
				scanf("%lf", dval);
				break;
			case 's':
				sval = va_arg(ap, char *);
				scanf("%s", sval);
				break;
			default:
				putchar(*p);
				break;
			}
		}
	}
	va_end(ap); /* очистка, когда все сделано */
}
