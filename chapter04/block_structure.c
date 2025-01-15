#include <stdio.h>

void f(double);

main()
{
	int n = 5, i = 3;

	printf("n = %d, i = %d\n", n, i);

	if (n > 0) {
		int i; /* declare a new i */
		for (i = 0; i < n; i++)
			printf("i = %d\n", i);
	}

	int x;
	int y;

	x = 3; y = 10;
	printf("x = %d, y = %d\n", x, y);

	f(1.5);

	return 0;
}

void f(double x)
{
	double y;

	y = .14;

	printf("x = %f, y = %f\n", x, y);

}
