#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define OPEN_MAX 20 /* max число одновременно открытых файлов */
#define PERMS 0666 /* RW для собственника, группы и проч. */

struct flags {
	unsigned int is_read  : 1; /* файл открыт на чтение */
	unsigned int is_write : 1; /* файл открыт на запись */
	unsigned int is_unbuf : 1; /* файл не буферизируется */
	unsigned int is_eof   : 1; /* в данном файле встретился EOF */
	unsigned int is_err   : 1; /* в данном файле встретилась ошибка */
};

typedef struct _my_iobuf {
	int cnt;            /* количество оставшихся символов */
	char *ptr;          /* позиция следующего символа */
	char *base;         /* адрес буфера */
	struct flags flag; /* режим  доступа */
	int fd;             /* дескриптор файла */
} MY_FILE;

MY_FILE _my_iob[OPEN_MAX];
MY_FILE *my_fopen(char *, char *);

int _fillbuf(MY_FILE *);

#undef getc             /* отменяем библиотечный getc и определяем свой: */
#define getc(p) (--(p)->cnt >= 0 \
			   ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

char *my_fgets(char *, int, MY_FILE *);
#define MAXLINE 20      /* длина строки */

int main(int argc, char *argv[])
{
	MY_FILE *fp;
	char line[MAXLINE], *prog = argv[0]; /* имя программы */
		
	while (--argc > 0) {
		if ((fp = my_fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "%s: не могу открыть файл %s\n", prog, *argv);
			exit(1);
		}
		else {
			fprintf(stdout, "%s: открыт файл %s:\n", prog, *argv);
			//fprintf(stdout, "%c\n", getc(fp));
			while (my_fgets(line, MAXLINE, fp) != NULL)
				fprintf(stdout, "%s", line);
		}
	}
	exit(0);
}

/* my_fopen: открывает файл, возвращает файловый указатель */
MY_FILE *my_fopen(char *name, char *mode)
{
	int fd;
	MY_FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _my_iob; fp < _my_iob + OPEN_MAX; fp++)
		if (fp->flag.is_read == 0 && fp->flag.is_write == 0)
			break;              /* найдена свободная позиция */
	if (fp >= _my_iob + OPEN_MAX)  /* нет свободной позиция */
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd ==-1) /* невозможен доступ по имени name */
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	if (*mode == 'r') {
		fp->flag.is_read  = 1;
		fp->flag.is_write = 0;
	}
	else {
		fp->flag.is_read  = 0;
		fp->flag.is_write = 1;
	}
	return fp;
}

/* _fillbuf: запрос памяти и заполнение буфера */
int _fillbuf(MY_FILE *fp)
{
	int bufsize;

	if (fp->flag.is_read == 0 ||
		fp->flag.is_eof == 1 ||
		fp->flag.is_err == 1)
		return EOF;
	bufsize = (fp->flag.is_unbuf == 1) ? 1 : BUFSIZ;
	if (fp->base == NULL) /* буфера еще нет */
	   if ((fp->base = (char *) malloc(bufsize)) == NULL)
		   return EOF; /* нельзя получить буфер */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag.is_eof = 1;
		else
			fp->flag.is_err = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

/* my_fgets: получает не более n символов из iop */
char *my_fgets(char *s, int n, MY_FILE *iop)
{
	register int c;
	register char *cs;

	cs = s;
	while (--n > 0 && (c = getc(iop)) != EOF)
		if ((*cs++ = c) == '\n')
			break;
	*cs= '\0';
	return (c == EOF && cs == s) ? NULL : s;
}
