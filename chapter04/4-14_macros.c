/*
 * Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of
 * type t. (Block structure will help). □
 */

#include <stdio.h>

#define swap(t,x,y) { t c; c = (x), (x) = (y), (y) = c; }
#define swapdowhile(t,x,y) do { t c; c = (x), (x) = (y), (y) = c; } while (0)

main()
{
	int a = 1, b = 2;
	float x = 3.14, y = 6.28;

	printf("Before swap\n");
	printf("a = %d b = %d\n", a, b);
	swap(int, a, b);
	printf("After swap\n");
	printf("a = %d b = %d\n", a, b);

	printf("Before swap\n");
	printf("x = %f y = %f\n", x, y);
	swap(float, x, y);
	printf("After swap\n");
	printf("x = %f y = %f\n", x, y);

	if (a > b)
		/*swap(int, a, b);  This version breaks because it will be replaced
							with { int c; c = (a), (a) = (b), (b) = c; }; and
							the extra semicolon outside the block finishes the
							if therefore the else becomes unatached and thus
							it's a syntax error. One solution is to not use a
							semicolon, like this:
		swap(int, a, b)
		                    but a better approach is to use a do while block. */
		swapdowhile(int, a, b);
	else
		printf("Already in order\n");

	return 0;
}
