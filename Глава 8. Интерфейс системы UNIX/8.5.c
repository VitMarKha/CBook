#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>      /* флажки чтения и записи */
#include <sys/stat.h>   /* структура, возвращаемая stat */
#include <dirent.h>     /* формат записи каталога */
#include <time.h>

void fsize(char *);

/* печатает размер файлов */
int main (int argc, char **argv)
{
	if (argc == 1)          /* по умолчанию берется текущий каталог */
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

void dirwalk(char *, void (*fcn)(char *));

/* fsize: печатает размер файла "name" */
void fsize(char *name)
{
	struct stat stbuf;
	struct tm * time_info;
	char timestr[5];  /* "HH:MM\0" */

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: нет доступа к %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	
	time_info = localtime(&stbuf.st_mtime);
	strftime(timestr, sizeof(stbuf.st_mtim), "%H:%M", time_info);
	printf("%ld %8ld %s %s\n", stbuf.st_ino, stbuf.st_size, timestr, name);
}

#define MAX_PATH 1024

/* dirwalk: применяет fcn ко всем файлам из dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: не могу открыть %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0
			|| strcmp(dp->d_name, "..") == 0)
			continue; /* пропустить себя и родителя */
		if (strlen(dir)+strlen(dp->d_name) + 2 > sizeof(name))
			fprintf(stderr, "dirwalk: слишком длинное имя %s/%s\n",
				dir, dp->d_name);
		else {
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn) (name);
		}
	}
	closedir(dfd);
}
