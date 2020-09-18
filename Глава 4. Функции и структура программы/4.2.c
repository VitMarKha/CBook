#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLEN 100

double atof(char s[]);

int main()
{
	  char in1[MAXLEN] = "  -10.325e-3\0";
	  char in2[MAXLEN] = "  -10.325e+3\0";

	  printf("in1 = %s\n", in1);
	  printf("out = %f\n\n", atof(in1));

	  printf("in2 = %s\n", in2);
	  printf("out = %f\n", atof(in2));

	  return 0;
}

/*atof: преобразование строки s в double */
double atof(char s[])
{
	double val, power, degval, base, exponent;
	int i, sign, degsign;

	for (i = 0; isspace(s[i]); i++);  /* игнорирование левых символов-разделителей */
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] =='-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	if (s[i] == 'e' || s[i] == 'E')
		i++;
	degsign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] =='-')
		i++;
	for (degval = 0.0; isdigit(s[i]); i++)
	degval = 10.0 * degval + (s[i] - '0');
	exponent = pow(10.0, degval);
	base = sign * (val / power);

	return degsign == 1 ? base * exponent : base / exponent;
}
