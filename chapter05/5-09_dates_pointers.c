/*
 * Exercise 5-9. Rewrite the routines day_of_year and month_day with pointers
 * instead of indexing. □
 */

#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int, int, int);
int month_day(int, int, int *, int *);
void print_day_of_year(int, int, int);
void print_month_day(int, int);

main()
{
	int day, month, year, yearday;

	year = 1989;
	month = 5;
	day = 31;
	print_day_of_year(year, month, day);
	yearday = 365;
	print_month_day(year, yearday);

	month = 2;
	day = 29;
	print_day_of_year(year, month, day);
	yearday = 366;
	print_month_day(year, yearday);

	year = 2004;
	print_day_of_year(year, month, day);
	print_month_day(year, yearday);
	return 0;
}

/* day_of_year:   set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (month < 1 || month > 12)
		return -1;
	if (day < 1 || day > *(*(daytab+leap)+month))
		return -1;
	for (i = 1; i < month; i++)
		day += *(*(daytab+leap)+i);
	return day;
}

/* month_day:  set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (yearday < 1 || yearday > 365+leap)
		return -1;
	for (i = 1; yearday > *(*(daytab+leap)+i); i++)
		yearday -= *(*(daytab+leap)+i);
	*pmonth = i;
	*pday = yearday;
	return 1;
}

/* print_day_of_year: prints day of year with error checking */
void print_day_of_year(int year, int m, int d)
{
	int yearday;

	yearday = day_of_year(year, m, d);
	if (yearday < 0)
		printf("Invalid month %d and/or day %d for year %d\n", m, d, year);
	else
		printf("%02d/%02d/%04d is the %2d-th day\n", d, m, year, yearday);
}

/* print_month_day: prints month and day with error checking */
void print_month_day(int year, int yearday)
{
	int d, m, ok;

	ok = month_day(year, yearday, &m, &d);
	if (ok < 0)
		printf("Invalid yearday: %d for year %d\n", yearday, year);
	else
		printf("The %2d-th day of the year %4d, is %02d/%02d/%04d\n", yearday, year, d, m, year);
}
