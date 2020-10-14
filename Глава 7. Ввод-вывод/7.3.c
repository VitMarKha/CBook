#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int	main(void)
{
	int x = 22;
	double y = 17.974;
	char c = 'r';
	char *s = "Now is end\n";
	
	minprintf("Hello %d %i %o %x %f %g %e %c %s\0",
						x, x, x, y, y, y, c, s);
	return (0);
}

/* minprintf: ограниченая версия printf
** со списком аргументов переменной длины
*/
void minprintf(char *fmt, ...)
{
	va_list ap; /* указатель на безымянные аргументы */
	char *p;
	char *sval;
	int ival;
	double dval;
	unsigned int uval;

	va_start(ap, fmt); /* установить ap на 1-й аргумент без имени */
	for (p = fmt; *p; p++)
	{
		if (*p != '%')
		{
			putchar(*p);
			continue;
		}
		switch (*++p)
		{
			case 'd':
				ival = va_arg(ap, int);
				printf("%d", ival);
				break;
			case 'i':
				ival = va_arg(ap, int);
				printf("%i", ival);
				break;
			case 'o':
				uval = va_arg(ap, unsigned int);
				printf("%o", uval);
				break;
			case 'x':
				uval = va_arg(ap, unsigned int);
				printf("%x", uval);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf("%f", dval);
				break;
			case 'g':
				dval = va_arg(ap, double);
				printf("%g", dval);
				break;
			case 'e':
				dval = va_arg(ap, double);
				printf("%e", dval);
				break;
			case 'c':
				ival = va_arg(ap, int);
				printf("%c", ival);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++)
					putchar(*sval);
				break;
			default:
				putchar(*sval);
				break;
		}
		va_end(ap);
	}
}
