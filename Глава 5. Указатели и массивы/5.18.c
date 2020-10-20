int gettoken(void) /* возвращает следующую лексему */
 {
	 int c;
	 void ungetch(int);
	 char *p = token;

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

 int getter(void)
 {
	 int c;
	 while ((c = getch()) == ' ' || c == '\t');
	 return c;
 }

/* dirdcl: разбор собственно объявителя */
 void dirdcl(void)
 {
	 int type;

	 if (tokentype == '(') {
		 dcl();
		 if (tokentype != ')') {
			 printf("oшибкa: пропущена )\n");
			 exit(-1);
		 }
	 } else if (tokentype == NAME) /* имя переменной */
		 strcpy(name, token);
	 else {
		 printf("ошибка: должно быть name или (dcl)\n");
		 exit(-1);
	 }

	 while((type = gettoken()) == PARENS || type == BRACKETS)
		 if (type == PARENS)
			 strcat(out, "функц. возвр.");
		 else {
			 strcat(out, " массив ");
			 strcat(out, token);
			 strcat(out, " из ");
		 }
 }
