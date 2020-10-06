#include <stdio.h>
#include <string.h>

int day_of_year(int year, int mouth, int day);
void mouth_day(int year, int yearday);

int	main(void)
{
	printf("%d\n", day_of_year(2000, 4, 18));
	mouth_day(1988, 70);
	return (0);
}

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: вычисления дня года по месяцу и дню используя указатель */
int day_of_year(int year, int mouth, int day)
{
	int i;
	int leap;
	char *tmp;

	i = 1;
	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	if (mouth > 12 || day > daytab[leap][mouth] ||
		year <= 0 || mouth <= 0 || day <= 0)
	{
		printf("Ошибка: не правильно введена дата\n");
		return (-1);
	}
	tmp = &daytab[leap][1];
	while (i < mouth)
	{
		tmp = &daytab[leap][i];
		day += *tmp;
		++i;
	}
	return (day);
}

/* mouth_day: вычисление месяца и даты по дню года используя указатель */
void mouth_day(int year, int yearday)
{
	int i;
	int leap;
	char *tmp;
	
	i = 1;
	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	if (year <= 0 || yearday <= 0 ||
		(yearday > 365 && leap == 0) ||
		(yearday > 366 && leap == 1))
	{
		printf("Ошибка: не правильно введена дата\n");
		return ;
	}
	while (yearday > daytab[leap][i])
	{
		tmp = &daytab[leap][i];
		yearday -= *tmp;
		++i;
	}
	printf("Mouth: %d\n", i);
	printf("Day: %d\n", yearday);
}
