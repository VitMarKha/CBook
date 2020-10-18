#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "unistd.h"

#define BUFSIZE 100

/* чтение файла и печать его в поток вывода */
int	main(int argc, char *argv[])
{
	int file;
	int n;
	char buf[BUFSIZE];

	if (argc != 2)
	{
		printf("Error 1\n");
		exit(1);
	}
	if ((file = open(argv[1], O_RDONLY, 0)) >= 0)
		while ((n = read(file, buf, BUFSIZE)) > 0)
			write(1, &buf, n);
	close(file);
	exit(0);
}
