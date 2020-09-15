#include <stdio.h>

#define T 10

int binsearch(int x, int v[], int n);
int fasrt_binsearch(int x, int v[], int n);

int	main(void)
{
	int v[T];
	int search = 9;
	int i;

	for(i = 0; i < T; ++i)
	{
		v[i] = i;
		printf("%d ", v[i]);
	}

	printf("\nBinsearch: %d\n", binsearch(search, v, 10));
	printf("Fasrt binsearch: %d", fasrt_binsearch(search, v, 10));
	return 0;
}

/* fasrt_binsearch: поиск x в v[0] <= v[1] <= ... <= v[n -1] */
int fasrt_binsearch(int x, int v[], int n)
{
	int low;
	int mid;
	int high;

	low = 0;
	high = n - 1;
	mid = (low + high) / 2;
	while (low <= high && x != v[mid])
	{
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
		mid = (low + high) / 2;
	}
	if (x == v[mid])
	{
		return (mid);
	}
	return (-1);
}

/* binsearch: поиск x в v[0] <= v[1] <= ... <= v[n -1] */
int binsearch(int x, int v[], int n)
{
	int low;
	int mid;
	int high;

	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return (mid);
	}
	return (-1);
}
