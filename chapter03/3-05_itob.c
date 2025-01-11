/*
 * Exercise 3-5. Write the function itob(n,s,b) that converts the integer n
 * into a base b character representation in the string s. In paritcular,
 * itob(n, s, 16) formats n as a hexadecimal integer in s. □
 */


#include <stdio.h>
#include <string.h>
#include <limits.h>

#define BUFFER 32

void reverse(char [], int);
void itob(int, char [], int);

main()
{
	int i;
	char a[BUFFER];

	i = 42;
	itob(i, a, 2);
	printf("%d in base 2 -> %s\n", i, a);

	i = 34;
	itob(i, a, 8);
	printf("%d in base 8 -> %s\n", i, a);

	i = 42;
	itob(i, a, 10);
	printf("%d in base 10 -> %s\n", i, a);


	i = 66;
	itob(i, a, 16);
	printf("%d in base 16 -> %s\n", i, a);

	i = 255;
	itob(i, a, 2);
	printf("%d in base 2 -> %s\n", i, a);

	i = 255;
	itob(i, a, 8);
	printf("%d in base 8 -> %s\n", i, a);

	i = 255;
	itob(i, a, 10);
	printf("%d in base 10 -> %s\n", i, a);


	i = 255;
	itob(i, a, 16);
	printf("%d in base 16 -> %s\n", i, a);

	i = -255;
	itob(i, a, 16);
	printf("%d in base 16 -> %s\n", i, a);

	i = 2748;
	itob(i, a, 16);
	printf("%d in base 16 -> %s\n", i, a);

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
void itob(int n, char s[], int b)
{
	int i, sign, digit;

	i = 0;
	if ((sign = n) < 0) {    /* record sign */
		if (n == INT_MIN) {  /* convert the last digit and add one */
			/* e.g. n = -128 */
			/* n % 10 = -8 */
			/* -(n % 10) = 8 */
			/* -(n % 10) + '0' = '8' */
			s[0] = -(n % b) + '0';
			i = 1;
			n /= -b;
		} else
			n = -n;          /* make n positive */
	}
	do {      /* generate digits in reverse order */
		digit = n % b;
		s[i++] = digit > 9 ? digit - 10 + 'A' : digit + '0';   /* get next digit */
	} while ((n /= b) > 0);     /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s, i);
}
