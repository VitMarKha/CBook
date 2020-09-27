#include <stdio.h>
#include <stdlib.h> /* Для объявления atof() */
#include <math.h> /* Для объявления floor() и pow() */

#define MAXOP 100 /* Максимальный размер операнда или знака */
#define NUMBER '0' /* сигнал, что обнаружено число */

int getop(char s[]);
void push(double f);
double pop(void);
double last_in_stack(void);
void duplication(void);
void print_all(void);
void clear_stack(void);
void revers_stack(void);
void optovar(int n, double f);
double vartoop(int n);

/* Калькулятор с обратной польско записью */
int main(void)
{
	int type;
	int in;
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
			case 'p':
				printf("Last in stack: %.3f\n", last_in_stack());
				break;
			case 'd':
				duplication();
				printf("Stack duplication done\n");
				break;
			case 'a':
				print_all();
				break;
			case 'c':
				clear_stack();
				printf("Stack is clear\n");
				break;
			case 's':
				revers_stack();
				printf("Reverse is done\n");
				break;
			case 'w':
				push(pow(pop(), pop()));
				break;
			case '>':
				in = 1;
				break;
			case 'A': case 'B': case 'C':
				if (in) {
					optovar(type, pop());
					in = 0;
				}
				else
					push(vartoop(type));
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
				printf("Last Answer: %.5g\n", pop());
				break;
			default:
				printf("Error: unknow command %s\n", s);
				break;
		}
	}
	return (0);
}

#define MAXVAL 100/* максимальная глубина стека */
#define MAXVAR 26

int sp = 0; /* следующая свободная позиция в стеке */
double val[MAXVAL]; /* стек операндов */
double var[MAXVAR]; /* стек переменных */

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
/* last_in_stack: взять с вершины стека и выдать в качестве результата */
double last_in_stack(void)
{
	if (sp > 0)
		return val[sp - 1];
	else
	{
		printf("Error: stack empty2\n");
		return (0.0);
	}
}

/* duplication: делает дубликат в последнего элемента в стеке */
void duplication(void)
{
	int tmp;
	if (sp > 0)
	{
		tmp = sp;
		val[sp] = val[sp - 1];
		++sp;
	}
	else
		printf("Error: stack empty3\n");
}

/* print_all: печатает все элементы стека */
void print_all(void)
{
	int i;
	
	i = 0;
	if (sp > 0)
	{
		while (i < sp)
		{
			printf("%.3f, ", val[i]);
			++i;
		}
	}
	else
		printf("Error: stack empty4\n");
	printf("\n");
}

/* clear_stack: очищает стек */
void clear_stack(void)
{
	int i;
	
	i = 0;
	if (sp > 0)
	{
		while (sp >= 0)
			val[sp--] = 0;
	}
	else
		printf("Error: stack empty5\n");
	printf("\n");
}

/* revers_stack: меняет местами последний и предпоследний элемент стека */
void revers_stack(void)
{
	double tmp1;
	double tmp2;
	int sp2;

	if (sp > 0)
	{
		sp2 = sp - 2;
		tmp1 = val[sp - 1];
		tmp2 = val[sp2];

		val[sp - 1] = tmp2;
		val[sp2] = tmp1;
	}
	else
		printf("Error: stack empty6\n");
}

/* optovar: поместить верхнюю ячейку стека в переменную */
  void optovar(int n, double f)
  {
	  var[n-'A'] = f;
  }

  /* vartoop: взять значение переменной и выдать в качестве результата */
  double vartoop(int n)
  {
	  return var[n-'A'];
  }

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: извлекает следующий операнд или знак операции */
int getop(char s[])
{
	static int last_c = 0;
	int i;
	int c;

	if (last_c == 0)
		c = getch();
	else
	{
		c = last_c;
		last_c = 0;
	}
	
	while ((s[0] = c) == ' ' || c == '\t')
		c = getch();
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
		last_c = c;
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* буфер для ungetch */
int bufp = 0; /* следующая свободная позицыя в buf */
				
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
