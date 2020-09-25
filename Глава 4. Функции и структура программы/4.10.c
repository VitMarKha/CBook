#include <stdio.h>
#include <stdlib.h> /* Для объявления atof() */
#include <math.h> /* Для объявления floor() и pow() */

#define MAXOP 100 /* максимальный размер операнда или знака */
#define NUMBER '0' /* сигнал, что обнаружено число */
#define MAXLINE 200 /* максимальная длинна строки */

int getop(char s[]);
void push(double f);
double pop(void);
int	get_line(char s[], int lim);

char line[MAXLINE];
int line_i;

/* Калькулятор с обратной польско записью */
int main(void)
{
	int type;
	double op2;
	char s[MAXOP];

	while (get_line(line, MAXLINE) != 0)
	{
		line_i = 0;
		while ((type = getop(s)) != '\0' )
		{
			switch (type)
			{
				case NUMBER:
					push(atof(s));
					break;
				case '+':
					push(pop() + pop());
					break;
				case '*':
					push(pop() * pop());
					break;
				case '-':
					op2 = pop();
					push(pop() - op2);
					break;
				case '/':
					op2 = pop();
					if (op2 != 0.0)
						push(pop() / op2);
					else
						printf("Error: zero divisoe\n");
					break;
				case '\n':
					printf("Last Answer: %.5g\n", pop());
					break;
				default:
					printf("Error: unknow command %s\n", s);
					break;
			}
		}
	}
	return (0);
}

int	get_line(char s[], int lim)
{
	int	i;
	int	c;

	i = 0;
	while (lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return (i);
}

#define MAXVAL 100 /* максимальная глубина стека */

int sp = 0; /* следующая свободная позиция в стеке */
double val[MAXVAL]; /* стек операндов */

/* push: помещает число f в стек оперендов */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("Error: stack full, can't push %g\n", f);
}

/* pop: извлекает и возвращает верхнее число из стека */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
	{
		printf("Error: stack empty1\n");
		return (0.0);
	}
}

#include <ctype.h>

/* getop: извлекает следующий операнд или знак операции */
int getop(char s[])
{
	int i;
	int c;

	while ((s[0] = c = line[line_i++]) == ' ' || c == '\t');
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c; /* не число */
	i = 0;
	if (isdigit(c)) /* накопление целой части */
		while (isdigit(s[++i] = c = line[line_i++]));
	if (c == '.') /* накопление дробной части */
		while (isdigit(s[++i] = c = line[line_i++]));
	s[i] = '\0';
	line_i--;

	return NUMBER;
}
