#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int, int, int);
void month_day(int, int, int *, int *);

main()
{
	int m, d, year, yearday;

	year = 1988;
	yearday = 60;
	month_day(year, yearday, &m, &d);
	printf("The %2d-th day of the year %4d, is %02d/%02d/%04d\n", yearday, year, d, m, year);
	d = 31;
	m = 5;
	year = 1989;
	printf("%02d/%02d/%04d is the %2d-th day\n", d, m, year, day_of_year(year, m, d));

	return 0;
}

/* day_of_year:   set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}
