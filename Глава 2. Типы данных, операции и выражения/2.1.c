#include <stdio.h>
#include <limits.h>
#include <float.h>

int	main(void)
{
	int				x;
	long int		xx;
	short int		xxx;
	unsigned int	xxxx;
	double			d;
	long double		dd;
	float			f;
	char			c;
	signed char		cc;
	unsigned char	ccc;

	printf("int в байтах: %lu\nint в max: %d\nint в min: %d\n", sizeof(x), INT_MAX, INT_MIN);
	printf("long int в байтах: %lu\nlong int в max: %ld\nlong int в min: %ld\n", sizeof(xx), LONG_MAX, LONG_MIN);
	printf("short int в байтах: %lu\nshort int в max: %d\nshort int в min: %d\n", sizeof(xxx), SHRT_MAX, SHRT_MIN);
	printf("unsigned int в байтах: %lu\nunsigned int в max: %d\nunsigned int в min: %d\n", sizeof(xxxx), UINT_MAX, 0);
	printf("double в байтах: %lu\ndouble в max: %f\ndouble в min: %f\n", sizeof(d), DBL_MIN, DBL_MAX);
	printf("long double в байтах: %lu\n", sizeof(dd));
	printf("float в байтах: %lu\nfloat в max: %f\nfloat в min: %f\n", sizeof(f), FLT_MIN, FLT_MAX);
	printf("char в байтах: %lu\nchar в max: %d\nchar в min: %d\n", sizeof(c), CHAR_MAX, CHAR_MIN);
	printf("signed char в байтах: %lu\nsigned char в max: %d\nsigned char в min: %d\n", sizeof(cc), SCHAR_MAX, SCHAR_MIN);
	printf("unsigned char в байтах: %lu\nunsigned char в max: %d\nunsigned char в min: %d\n", sizeof(ccc), UCHAR_MAX, 0);
	return (0);
}
