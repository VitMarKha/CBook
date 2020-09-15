#include <stdio.h>

int		any(char s1[], char s2[]);

int		main(void)
{
	char	line_one[] = "test string\0";
	char	line_two[] = "ring\0";
	printf("Str 1: %s\n", line_one);
	printf("Str 2: %s\n", line_two);
	printf("Any: %d\n", any(line_one, line_two));
	return (0);
}

/* any: возвращает номер первыой позиции в s1 который находится какой либо символ из строки s2 */
int		any(char s1[], char s2[])
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		while (s1[i] != s2[j] && s2[j] != '\0')
			++j;
		if (s1[i] == s2[j])
		{
			return (i);
		}
		j = 0;
		++i;
	}
	return (-1);
}
