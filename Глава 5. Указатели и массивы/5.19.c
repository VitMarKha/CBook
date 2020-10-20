#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};

int gettoken(void);
int nexttoken(void);
int getter(void);
int tokentype;           /* тип последней лексемы */
char token[MAXTOKEN];    /* текст последней лексемы */
char name[MAXTOKEN];     /* имя */
char datatype[MAXTOKEN]; /* тип = char, int и т.д. */
char out[1000];          /* выдаваемый текст */

/* undcl: преобразует словесное описание в объявление */
int main(void)
{
	int type;
	char temp[MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*' ) {
				if ((type = nexttoken()) == PARENS || type == BRACKETS)
					sprintf(temp, "(*%s)", out);
				else
					sprintf(temp, "*%s", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf("неверный элемент %s во фразе\n", token);
		printf("%s\n", out);
	}
	return 0;
}

enum {NO, YES};
int prevtoken = NO;

int nexttoken(void)
{
	int type;
	type = gettoken();
	prevtoken = YES;
	return type;
}

int getch(void);

int gettoken(void) /* возвращает следующую лексему */
{
	int c;
	void ungetch(int);
	char *p = token;

	if (prevtoken == YES) {
		prevtoken = NO;
		return tokentype;
	}

	if ((c = getter()) == '(') {
		if ((c = getter()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '['){
		for (*p++ = c; (*p++ = getter()) != ']'; );
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}
