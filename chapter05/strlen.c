#include <stdio.h>
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#undef strlen

int strlen(char *);

main()
{
	printf("len: %d\n", strlen("I'm a potato"));
	return 0;
}

/* strlen:  return length of string s */
int strlen(char *s)
{
	int n;

	for (n = 0; *s != '\0'; s++)
		n++;
	return n;
}
