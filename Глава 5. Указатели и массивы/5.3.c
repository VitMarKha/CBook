#include <stdio.h>
#include <string.h>

#define SIZE 20

void strcat2(char *s, char *t);

int	main(void)
{
	char c1[SIZE] = "Hello ";
	char c2[SIZE] = "World";
	strcat2(c1, c2);
	printf("%s", c1);
	return (0);
}

/* strcat: кописрует строки t в конец строки s */
void strcat2(char *s, char *t)
{
	while (*s != '\0')
		s++;
	while ((*s++ = *t++) != '\0');
}
