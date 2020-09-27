#include <stdio.h>

void reverse_recursive(char s[], int start, int end);
int strlenf(char s[]);

int main(void)
{
	char str[] = "I am here";
	reverse_recursive(str, 0, strlenf(str) - 1);
	printf("%s", str);
	return (0);
}

/* reverse: рекурсивная функция разваорачивающая строку */
void reverse_recursive(char s[], int first, int last)
{
	char c;

	c = s[first];
	s[first++] = s[last];
	s[last--] = c;
	if (first != last)
		reverse_recursive(s, first, last);
}

int strlenf(char s[])
{
	int i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}
