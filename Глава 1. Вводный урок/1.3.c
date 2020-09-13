#include <stdio.h>

int	main(void)
{
	float	fahr;
	float	celsius;
	int		lower;
	int		step;
	int		upper;

	lower = 0;
	upper = 300;
	step = 20;
	fahr = lower;
	printf("  Pharyngate and Celsius table:\n");
	while (fahr <= upper)
	{
		celsius = (5.0 / 9.0) * (fahr - 32.0);
		printf("%9.0f %12.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
	return (0);
}
