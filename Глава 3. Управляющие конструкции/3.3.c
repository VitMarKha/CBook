#include <stdio.h>

#define MAXLINE 1000

void expand(char s1[], char s2[]);

int	main(void)
{
	char s1[] = "-1-9-A-Z-g-o-}\0";
	char s2[MAXLINE];
	
	printf("Str one: %s\n", s1);
	expand(s1, s2);
	printf("Str two after expand: %s\n", s2);

	return 0;
}

void expand(char s1[], char s2[])
{
	int i;
	int j;
	int plus;
	int difference;
	char start;
	char finish;

	i = 0;
	j = 0;
	plus = 0;
	if (s1[i] == '-')
		++i;
	while (s1[i] != '\0')
	{
		if (s1[i + 1] == '-')
		{
			start = s1[i];
			finish = s1[i + 2];
			difference = s1[i + 2] - s1[i];
			while (difference-- != 0)
				s2[j++] = (int)s1[i] + (plus++);
		}
		plus = 0;
		++i;
	}
	s2[j++] = finish;
	s2[j] = '\0';
}
