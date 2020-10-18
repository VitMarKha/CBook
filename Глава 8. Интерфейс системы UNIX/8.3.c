#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define OPEN_MAX 20 /* max число одновременно открытых файлов */
#define PERMS 0666 /* RW для собственника, группы и проч. */
#define MY_BUFSIZ 2 /* маленький размер буфера для проверки _flushbuf */

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

int _flushbuf(int, MY_FILE *);

#undef putc         /* отменяем библиотечный putc */
#define putc(x,p) (--(p)->cnt >= 0 \
			   ? *(p)->ptr++ = (x) : _flushbuf((x),p))


int main(int argc, char *argv[])
{
	MY_FILE *fp;
	char c, *prog = argv[0]; /* имя программы */
		
	while (--argc > 0) {
		if ((fp = my_fopen(*++argv, "w")) == NULL) {
			fprintf(stderr, "%s: не могу открыть файл %s\n", prog, *argv);
			exit(1);
		}
		else {
			fprintf(stdout, "%s: файл %s открыт на запись:\n", prog, *argv);
			while ((c = getc(stdin)) != EOF) {
				putc(c, fp);
			}
			fprintf(stdout, "%s: запись в файл %s завершена.\n", prog, *argv);
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

/* _flushbuf: запрос памяти и очистка буфера */
int _flushbuf(int x, MY_FILE *fp)
{
	int bufsize, numchar;

	if (fp->flag.is_write == 0 ||
		fp->flag.is_eof == 1 ||
		fp->flag.is_err == 1)
		return EOF;
	bufsize = (fp->flag.is_unbuf == 1) ? 1 : MY_BUFSIZ;
	if (fp->base == NULL) { /* буфера еще нет */
		if ((fp->base = (char *) malloc(bufsize)) == NULL) {
			fp->flag.is_err = 1;
			return EOF; /* нельзя получить буфер */
		}
	}
	else {
		numchar = fp->ptr - fp->base;
		if (write(fp->fd, fp->base, numchar) != numchar) {
		   fp->flag.is_err = 1;
		   return EOF; /* ошибка записи */
	   }
	}
	fp->ptr = fp->base;
	*fp->ptr++ = (unsigned char) x;
	fp->cnt = bufsize - 1;
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag.is_eof = 1;
		else
			fp->flag.is_err = 1;
		return EOF;
	}
	return x;
}

/* fflush: очистка буфера, соответствующего файлу fp */
int my_fflush(MY_FILE *fp)
{
   int ret = 0;

   if (fp->flag.is_write)
	   ret = _flushbuf(0, fp);
   fp->ptr = fp->base;
   fp->cnt = (fp->flag.is_unbuf == 1) ? 1 : BUFSIZ;
   return ret;
}

/* fclose: закрыть файл fp */
 int my_fclose(MY_FILE *fp)
 {
	int ret;

	if ((ret = my_fflush(fp)) != EOF) {
		free (fp->base);
		fp->ptr = NULL;
		fp->base = NULL;
		fp->cnt = 0;
		fp->flag.is_read = 0;
		fp->flag.is_write = 0;
	}
	return ret;
 }
