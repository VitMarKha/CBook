#include <stdio.h>

#define MAXLINE 1000

void escape(char s[], char t[]);

int	main(void)
{
	char str1[MAXLINE] = "123\t456\nasdasda\0";
	char str2[MAXLINE];
	printf("Str1: %s\n", str1);
	printf("Str2: %s\n", str2);
	escape(str1, str2);
	printf("Str2 after escape: %s", str2);
	return 0;
}

void escape(char s[], char t[])
{
	int i;
	int j;
	char c;

	i = 0;
	j = 0;
	while ((c = s[i]) != '\0')
	{
		switch (c)
		{
			case '\t' :
				t[j++] = '\\';
				t[j] = 't';
				break ;
			case '\n' :
				t[j++] = '\\';
				t[j] = 'n';
				break ;
			default:
				t[j] = c;
				break ;
		}
		++j;
		++i;
	}
	t[j] = '\0';
}
