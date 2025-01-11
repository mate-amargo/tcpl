/*
 * Exercise 3-6. Write a version of itoa that accepts three arguments instead
 * of two. The third argument is a minimum field width; the converted number
 * must be padded with blanks on the left if necessary to make it wide enough.
 * □
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define BUFFER 32

void reverse(char [], int);
void itoa(int, char [], int);

main()
{
	int i;
	char a[BUFFER];

	i = 128;
	itoa(i, a, 3);
	printf("%s\n", a);

	i = 128;
	itoa(i, a, 8);
	printf("%s\n", a);

	i = 12345678;
	itoa(i, a, 8);
	printf("%s\n", a);

	return 0;
}

/* reverse: reverse a string s in place of length n (not counting '\0') */
void reverse(char s[], int n)
{
	int c, i, j;

	for (i = 0, j = n-1; i < j; i++, j--) {
		c = s[i], s[i] = s[j], s[j] = c;
	}
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[], int p)
{
	int i, sign;

	i = 0;
	if ((sign = n) < 0) {    /* record sign */
		if (n == INT_MIN) {  /* convert the last digit and add one */
			/* e.g. n = -128 */
			/* n % 10 = -8 */
			/* -(n % 10) = 8 */
			/* -(n % 10) + '0' = '8' */
			s[0] = -(n % 10) + '0';
			i = 1;
			n /= -10;
		} else
			n = -n;          /* make n positive */
	}
	do {      /* generate digits in reverse order */
		s[i++] = n % 10 + '0';   /* get next digit */
	} while ((n /= 10) > 0);     /* delete it */
	if (sign < 0)
		s[i++] = '-';
	for (; i < p; i++)
		s[i] = ' ';
	s[i] = '\0';
	reverse(s, i);
}
