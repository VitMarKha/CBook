#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100  /* макс. размер операнда или оператора */
#define NUMBER '0' /* признак числа */

int getop (char *);
void push (double);
double pop (void);

/* калькулятор с обратной польской записью */
int main()
{
   int op;
   double op2;
   char s[MAXOP];

   while ((op = scanf("%s", s)) && op != EOF) {
	   switch (getop(s)) {
	   case NUMBER:
		   push (atof(s));
		   break;
	   case '+':
		   push (pop() + pop());
		   break;
	   case '*':
		   push (pop() * pop());
		   break;
	   case '-':
		   op2 = pop();
		   push (pop() - op2);
		   break;
	   case '/':
		   op2 = pop();
		   if (op2 != 0.0)
			   push (pop() / op2);
		   else
			   printf("ошибка: деление на нуль\n");
		   break;
	   default:
		   printf("ошибка: неизвестная операция %s\n", s);
		   break;
	   }
   }
   printf("\t%.8g\n", pop());

   return 0;
}

/* getop: получает следующий оператор или операнд */
int getop(char *s)
{
   if (!isdigit(s[0]) && s[0] != '.')
	   return s[0];    /* не число */
   else
	   return NUMBER;
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
