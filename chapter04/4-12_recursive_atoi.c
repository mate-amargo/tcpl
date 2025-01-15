/*
 * Exercise 4-12. Adapt the ideas of printd to write a recursive version of
 * itoa; that is, convert an integer into a string by calling a recoursive
 * routine. □
 */

#include <stdio.h>
#include <limits.h>

#define BUFFER 32

void itoa(int, char []);

main()
{
	int i;
	char a[BUFFER];

	i = 123; a[0] = '\0';
	itoa(i, a);
	printf("%d -> %s\n", i, a);

	i = 2147483647; a[0] = '\0';
	itoa(i, a);
	printf("%d -> %s\n", i, a);


	i = -2147483647; a[0] = '\0';
	itoa(i, a);
	printf("%d -> %s\n", i, a);

	i = -2147483648; a[0] = '\0';
	itoa(i, a);
	printf("%d -> %s\n", i, a);

	return 0;
}

/* itoa: convert integer n to a string s*/
void itoa(int n, char s[])
{
	int i, size;

	if (n < 0) {
		s[0] = '-';
		s[1] = '\0';
		if (n == INT_MIN) {  /* can't do n = -n */
			i = n; size = 1;
			while (i/10) {
				i /= 10;
				size *= 10;
			}
			i = -i;
			s[1] = i % 10 + '0'; /* add first digit */
			s[2] = '\0';
			n = n % size; /* chop first digit */
		}
		n = -n;          /* make n positive */
	}
	if (n / 10)
		itoa(n / 10, s);
	i = 0;
	while (s[i] != '\0')
		i++;
	s[i] = n % 10 + '0';
	s[i+1] = '\0';
}
