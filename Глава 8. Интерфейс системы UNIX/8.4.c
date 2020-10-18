/* my_fseek: смещает текущую позицию в fp на offset относительно origin */
 int my_fseek(MY_FILE *fp, long offset, int origin)
 {
	 int ret;
	 int numchar;

	if (fp->flag.is_read)
	{
		if (origin == 1)
			offset -= fp->cnt;
		lseek(fp->fd, offset, origin);
		fp->cnt = 0;
	}
	else if (fp->flag.is_write)
	{
		if ((numchar = fp->ptr - fp->base) > 0)
			if (write(fp->fd, fp->base, numchar) != numchar) {
				ret = -1;
		if (ret != -1) /* если нет ошибок */
			lseek(fp->fd, offset, origin);
	   }
	}
	return ret == -1 ? - 1 : 0;
 }
