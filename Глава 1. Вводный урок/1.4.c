#include <stdio.h>

int	main(void)
{
	float	fahr;
	float	celsius;
	int		lower;
	int		step;
	int		upper;

	lower = 0;
	upper = 15;
	step = 1;
	celsius = lower;
	printf("  Celsius and Pharyngate table:\n");
	while (celsius <= upper)
	{
		fahr = (celsius * (9.0 / 5.0)) + 32;
		printf("%9.1f %12.1f\n", celsius, fahr);
		celsius = celsius + step;
	}
	return (0);
}
