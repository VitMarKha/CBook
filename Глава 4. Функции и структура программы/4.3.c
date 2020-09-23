#include <stdio.h>
#include <stdlib.h> /* Для объявления atof() */
#include <math.h> /* Для объявления floor() */

#define MAXOP 100 /* Максимальный размер операнда или знака */
#define NUMBER '0' /* сигнал, что обнаружено число */

int getop(char s[]);
void push(double f);
double pop(void);

/* Калькулятор с обратной польско записью */
int main(void)
{
	int type;
	double op1;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF )
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
			case '%':
				op2 = pop();
				if (op2 != 0.0)
				{
					op1 = pop();
					push(op1 - op2 * floor(op1 / op2));
				}
				else
					printf("Error: zero divisoe\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("Error: unknow command %s\n", s);
				break;
		}
	}
	return (0);
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
		printf("Error: stack empty\n");
		return (0.0);
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: извлекает следующий операнд или знак операции */
int getop(char s[])
{
	int i;
	int c;
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c; /* не число */
	i = 0;
	if (isdigit(c)) /* накопление целой части */
		while (isdigit(s[++i] = c = getch()));
	if (c == '.') /* накопление дробной части */
		while (isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
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
