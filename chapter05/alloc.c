#include <stdio.h>

#define ALLOCSIZE 1000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	} else
		return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

main()
{
	char *p;

	p = alloc(5);
	p[0] = 'H';
	p[1] = 'e';
	p[2] = 'l';
	p[3] = 'l';
	p[4] = 'o';
	p[5] = '\0';
	printf("%s\n", p);
	afree(p);
	p[0] = 'B';
	p[1] = 'y';
	p[2] = 'e';
	p[3] = '!';
	p[4] = '\0';
	printf("%s\n", p);
	afree(p);

	return 0;
}
