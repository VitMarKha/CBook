void dirdcl(void)
 {
	 int type;
	 void params_dcl(void);

	 if (tokentype == '(') {
		 dcl();
		 if (tokentype != ')') {
			 printf("oшибкa: пропущена )\n");
			 exit(-1);
		 }
	 } else if (tokentype == NAME) {
		 if (name[0] == '\0')
			 strcpy(name, token);
	 }
	 else {
		 prevtoken = YES;
	 }

	 while((type = gettoken()) == PARENS ||
						type == BRACKETS ||
						type == '(')
		 if (type == PARENS)
			 strcat(out, "функц. возвр.");
		 else if (type == '(') {
			 strcat(out, " функц. приним. ");
			 params_dcl();
			 strcat(out, " и возвр. ");
		 }
		 else {
			 strcat(out, " массив ");
			 strcat(out, token);
			 strcat(out, " из ");
		 }
 }

void params_dcl(void)
 {
	 void type_dcl(void);

	 do {
		 type_dcl();
	 } while (tokentype == ',');
	 if (tokentype != ')') {
		 printf("oшибкa: пропущена ) в объявлении параметров\n");
		 prevtoken = YES;
	 }
 }

 void type_dcl(void)
 {
	 char t[MAXTOKEN];
	 int istypename(char []);
	 int istypequal(char []);

	 t[0] = '\0';
	 gettoken();

	 do {
		 if (tokentype != NAME) {
			 prevtoken = YES;
			 dcl();
		 }
		 else if (istypename(token)) {
			 strcat(t, token);
			 gettoken();
		 }
		 else if (istypequal(token)) {
			 strcat(t, token);
			 gettoken();
		 }
		 else {
			 printf("ошибка: неизвестный параметр %s\n", token);
			 prevtoken = YES;
		 }
	 } while (tokentype == ',' && tokentype == ')');
	 strcat(out, t);
	 if (tokentype == ',')
		 strcat(out, ", ");
 }

 int istypename(char name[])
 {
	 int i=0;
	 char *types[] = {"char", "int", "float"};
	 int ntypes = 3;

	 while (ntypes--)
		 if (strcmp(name, types[i++]) == 0)
			 return 1;

	 return 0;
 }

 int istypequal(char qual[])
 {
	 int i=0;
	 char *quals[] = {"const", "volatile"};
	 int nquals = 2;

	 while (nquals--)
		 if (strcmp(qual, quals[i++]) == 0)
			 return 1;

	 return 0;
 }
