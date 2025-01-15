/*
 * Exercise 4-2. Extend atof to handle scientific notation of the form
 *       123.45e-6
 * where a floating-point number may be followed by e or E and an optionally
 * signed exponent. □
 */

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

/* rudimentary calculator */
main()
{
	double sum, atof(char []);
	char line[MAXLINE];
	int getline(char line[], int max);

	sum = 0;
	while (getline(line, MAXLINE) > 0)
		printf("\t%g\n", sum += atof(line));
	return 0;
}

/* getline: get line into s, return length */
int getline(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* atof: convert string s to double, accepts scientific notation */
double atof(char s[])
{
	double val, power;
	int i, sign, sign_exponent, exponent;

	for (i = 0; isspace(s[i]); i++)  /* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power /= 10.0;
	}
	if (s[i] == 'e' || s[i] == 'E')
		i++;
		sign_exponent = 1;
		if (s[i] == '+' || s[i] == '-') {
			sign_exponent = (s[i] == '-') ? -1 : 1;
			i++;
		}
		for (exponent = 0; isdigit(s[i]); i++)
			exponent = 10.0 * exponent + (s[i] - '0');
		if (sign_exponent > 0) {
			for (i = 0; i < exponent; i++)
				power *= 10.0;
		} else {
			for (i = 0; i < exponent; i++)
				power /= 10.0;
		}
	return sign * val * power;
}
