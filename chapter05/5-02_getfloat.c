/*
 * Exercise 5-2. Write getfloat, the floating-point analog of getint. What type
 * does getfloat return as its function value? □
 */

/* getfloat still returns an int, to indicate EOF, >0 for successful convertion
 * or 0 for wrong input.
 */

#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */


int getch(void);
void ungetch(int);
int getfloat(float *);

main()
{
	int result;
	float x;

	printf("Gimme some number ");
	result = getfloat(&x);
	switch (result) {
		case EOF:
			printf("End of File\n");
			break;
		case 0:
			printf("I didn't get a valid number\n");
			break;
		default:
			printf("I got %f\n", x);
			break;
	}
	return 0;
}

/* getfloat:  get next float from input into *pn */
int getfloat(float *pn)
{
	int c, sign;
	float d;

	while (isspace(c = getch()))   /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);    /* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1 ;
	if (c == '+' || c == '-')
		c = getch();
	if (!isdigit(c) && c != '.') {
		ungetch(c);
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	if (c == '.') { /* find decimal part */
		c = getch();
		for (d = 10.0; isdigit(c); c = getch(), d *= 10.0)
			*pn = *pn + (c - '0')/(d);
		ungetch(c);
	}

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
