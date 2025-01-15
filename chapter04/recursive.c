#include <stdio.h>

void printd(int);

main()
{
	printd(-2147483647);
	putchar('\n');
	printd(-2147483648);
	putchar('\n');
	printd(2147483647);
	putchar('\n');
	printd(123);
	putchar('\n');

	return 0;
}

/* printd: print n in decimal */
void printd(int n)
{
	if (n < 0) {
		putchar('-');
		n = -n;
	}
	if (n / 10)
		printd(n / 10);
	putchar(n % 10 + '0');
}
