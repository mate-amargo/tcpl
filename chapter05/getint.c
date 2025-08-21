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
	printf("I got %d\n", x);
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
