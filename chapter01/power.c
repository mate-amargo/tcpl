#include <stdio.h>

int power(int m, int n);

/* test power function */
main()
{
	int i;

	for (i = 0; i < 10; ++i)
		printf("%d %d %d\n", i, power(2,i), power(-3, i));
	return 0;
}

/* power: raise base to n-th power; n >= 0 */
int power(int base, int n)
{
	int i, p;

	p = 1;
	for (i = 1; i <= n; ++i)
		p = p * base;
	return p;
}

/* power: raise base to n-th power; n >= 0 */
/* (old-style) version */
/*
   power(base, n)
   int base, n;
   {
   ... body is the same
   }

   The function prototype (declaration)
   would have looked like:
   int power();
   yeah, without any parameters, and since the default
   return type is int, the declaration could've been
   entirely ommited.
   */

/* power: raise base to n-th power; n>=; version 2 */
int power2(int base, int n)
{
	int p;

	for (p = 1; n > 0; --n)
		p = p * base;
	return p;
}
