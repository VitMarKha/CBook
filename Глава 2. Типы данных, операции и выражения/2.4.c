#include <stdio.h>

void	squeeze(char s1[], char s2[]);
int		is_here(char s1[], char s2[]);

int		main(void)
{
	char	line_one[] = "BHiartpphdayy\0";
	char	line_two[] = "Happy\0";
	printf("Str 1: %s\n", line_one);
	printf("Str 2: %s\n", line_two);
	squeeze(line_one, line_two);
	printf("New str: %s\n", line_one);
	return (0);
}

/* squeeze: удаляет все символы s2 из s1 */
void	squeeze(char s1[], char s2[])
{
	int i;
	int j;
	int tmp;
	int tmp2;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		while (s1[i] != s2[j] && s2[j] != '\0')
			++j;
		if (s1[i] == s2[j])
		{
			tmp = i + 1;
			s1[i] = s1[tmp];
			while (s1[tmp] != '\0')
			{
				tmp2 = tmp + 1;
				s1[tmp] = s1[tmp2];
				++tmp;
			}
		}
		j = 0;
		++i;
	}
	s1[i] = '\0';
	if (is_here(s1, s2))
		squeeze(s1, s2);
}

/* is_here: проверяет есть ли в s1 символы из s2 */
int		is_here(char s1[], char s2[])
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
			return (1);
		}
		j = 0;
		++i;
	}
	return (0);
}
