#include <stdio.h>
#include <stdlib.h> /* Для объявления atof() */

#define MAXOP 100 /* Максимальный размер операнда или знака */
#define NUMBER '0' /* сигнал, что обнаружено число */

int getop(char *s);
void push(int i);
int pop(void);

/*
** Калькулятор с обратной польско записью
*/

int		main(int argc, char *argv[])
{
	int		type;
	int		op2;
	char	s[MAXOP];
	int		err = 0;

	while ((--argc > 0) && (type = getop(*++argv)))
	{
		switch (type)
		{
			case NUMBER:
				push(atoi(*argv));
				break ;
			case '+':
				push(pop() + pop());
				break ;
			case '*':
				push(pop() * pop());
				break ;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break ;
			case '/':
				op2 = pop();
				if (op2 != 0)
					push(pop() / op2);
				else
					printf("Error: zero divisoe\n");
				break ;
			default:
				err = 1;
				printf("Error: unknow command %s\n", s);
				break ;
		}
	}
	if (!err)
		printf("%d\n", pop());
	return (0);
}

#define MAXVAL 10 /* максимальная глубина стека */

int		sp = 0; /* следующая свободная позиция в стеке */
double	val[MAXVAL]; /* стек операндов */

/*
** push: помещает число f в стек оперендов
*/

void	push(int i)
{
	if (sp < MAXVAL)
		val[sp++] = i;
	else
		printf("Error: stack full, can't push %d\n", i);
}
				
/*
** pop: извлекает и возвращает верхнее число из стека
*/

int	pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
	{
		printf("Error: stack empty\n");
		return (0);
	}
}

#include <ctype.h>
int strlenf(char *s);

/*
** getop: извлекает следующий операнд или знак операции
*/

int		getop(char *s)
{
	int c;
	int p;
	char *tmp;

	c = strlenf(s);
	p = 0;
	tmp = s;
	while (isdigit(*tmp++))
		++p;
	if (p != c)
		return *s; /* не число */
	else
		return NUMBER;
}

int strlenf(char *s)
{
	int i;

	i = 0;
	while (*s++ != '\0')
		++i;
	return (i);
}
