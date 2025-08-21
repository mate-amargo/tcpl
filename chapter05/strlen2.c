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
	char *p = s;
	while (*p != '\0')
		p++;
	return p - s;
}
