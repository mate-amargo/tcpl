/*
 * Exercise 5-1. As written, getint treats a + or - not followed by a digit as
 * a valid representation of zero. Fix it to push such a character back on the
 * input. □
 */

#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */


int getch(void);
void ungetch(int);
int getint(int *);

main()
{
	int result;
	int x;

	printf("Gimme some number ");
	result = getint(&x);
	switch (result) {
		case EOF:
			printf("End of File\n");
			break;
		case 0:
			printf("I didn't get a valid number\n");
			break;
		default:
			printf("I got %d\n", x);
			break;
	}
	return 0;
}

/* getint:  get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch()))   /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);    /* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1 ;
	if (c == '+' || c == '-')
		c = getch();
	if (!isdigit(c)) {
		ungetch(c);
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int getch(void) /* get a (possibly pushed back) character */
{
	int c;
	while (1) {
		c = (bufp > 0) ? buf[--bufp] : getchar();
		if (c != EOF)
			return c;
	}
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
