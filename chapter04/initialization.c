#include <stdio.h>

int a; /* variable definition, i.e. it assings storage */
int b = 10; /* variable definition, with initialization */

main()
{
	printf("In the absense of explicit initialization, external and static\n");
	printf("variables are guaranteed to be initialized to zero; automatic and\n");
	printf("register variables have undefined (i.e., garbage) initial\n");
	printf("values.\n");

	extern int a;   /* external variable declaration, since it was not initialized, it's set to zero */
	extern int b;   /* external variable declaration, already initialized */
	static int c;   /* static variable */
	int d;          /* automatic variable, not initialized, therefore it will have garbage */
	register int e; /* register variable, not initialized, therefore it will have garbage */

	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("c = %d\n", c);
	printf("d = %d\n", d);
	printf("e = %d\n", e);

	return 0;
}
