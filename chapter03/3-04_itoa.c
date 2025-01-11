/*
 * Exercise 3-4. In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n
 * equal to -(2^{wordsize-1}). Explain why not. Modify it to print that value
 * correctly, regardless of the machine on which it runs. □
 */


/*
 * Explanation: The problem comes from the line saying `n = -n`
 * In two's complement the MSB indicates the sign.
 * If the wordsize is, say, 8 bits, then, the largest negative number that can
 * be represented is:
 * 10000000
 * which is -2^(8-1) = -128.
 * Doing n = -n equates to flipping all the bits and adding one, which produces
 * 01111111 -> 10000000 = -128
 * So you get a negative number again! The same -128.
 * The largest positive number representable with 8bits in two's complement
 * is 2^(8-1) - 1 = 127.
 * Therefore, you can't get 128.
 * This will always happen for any number of bits in two's complement, because
 * there's always an extra negative number in the range, and 2^{wordsize-1} is
 * not representable for that wordsize.
 */

#include <stdio.h>
#include <limits.h>

#define BUFFER 32

void reverse(char [], int);
void itoa(int, char []);

main()
{
	int i;
	char a[BUFFER];

	i = 2147483647;
	itoa(i, a);
	printf("%d -> %s\n", i, a);


	i = -2147483647;
	itoa(i, a);
	printf("%d -> %s\n", i, a);

	i = -2147483648;
	itoa(i, a);
	printf("%d -> %s\n", i, a);

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
void itoa(int n, char s[])
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
	s[i] = '\0';
	reverse(s, i);
}
