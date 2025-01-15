/*
 * Exercise 4-7. Write a routine ungets(s) that will push back an entire string
 * onto the input. Should ungets know about buf and bufp, or should it just use
 * ungetch? □
 */

/* I'll use buf and bufp directly in this excercise, and I'll use ungetch on
 * excercise 9.
 */

#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <math.h>   /* compile with -lm */

#define MAXOP           100  /* max size of operand or operator */
#define NUMBER          '0'  /* signal that a number was found */
#define PRINT_TOP_STACK 'P'  /* singal to print the top of the stack */
#define DUP_TOP_STACK   'D'  /* singal to duplicate the top of the stack */
#define SWAP_TOP_STACK  'R'  /* swap the top two elements of the stack */
#define CLEAR_STACK     'L'  /* signal to clear the stack */
#define QUIT            'Q'  /* Quit the program. Wasn't part of ex, but fun */
#define EXP             'E'  /* exponential function; exp(x) */
#define SIN             'S'  /* sine of x; sin(x) */
#define COS             'C'  /* cosine of x; cos(x) */
#define TAN             'T'  /* tangent of x; tan(x) */
#define POW             'W'  /* x^y; pow(x, y) */
#define TEST_UNGETS     'X'  /* debug to test ungets */
#define MAXVAL          100  /* maximum depth of val stack */
#define MAXVARS         27   /* 26 letters plus '_' for last printed value */

int sp = 0;            /* next free stack position */
double val[MAXVAL];    /* value stack */
double vars[MAXVARS];  /* The last place holds the last printed value */

int getop(char []);
void push(double);
double pop(void);
int dtoabsi(double);
double modulus(double, double);
void test_ungets(void);

/* reverse Polish calculator */
main()
{
	int type;
	double op2, op3;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case PRINT_TOP_STACK:
				if (sp == 0)
					printf("the stack is empty\n");
				else
					printf("-> %g\n", vars[MAXVARS-1] = val[sp]);
				break;
			case DUP_TOP_STACK:
				op2 = pop();
				push(op2);
				push(op2);
				break;
			case SWAP_TOP_STACK:
				op2 = pop();
				op3 = pop();
				push(op2);
				push(op3);
				break;
			case CLEAR_STACK:
				sp = 0;
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0) {
					push(modulus(pop(), op2));
				} else
					printf("error: zero divisor\n");
				break;
			case EXP:
				push(exp(pop()));
				break;
			case SIN:
				push(sin(pop()));
				break;
			case COS:
				push(cos(pop()));
				break;
			case TAN:
				push(tan(pop()));
				break;
			case POW:
				op2 = pop();
				push(pow(pop(), op2));
				break;
			case TEST_UNGETS:
				test_ungets();
				break;
			case '\n':
				printf("\t%.8g\n", vars[MAXVARS-1] = pop());
				break;
			case QUIT:
				return 0;
			default:
				if (type >= 'a' && type <= 'z') /* use the value of var */
					push(vars[type - 'a']);
				else if (type == '_')
					push(vars[MAXVARS-1]);
				else
					printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}


/* push:  push f onto the stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop:  pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);
void ungets(char *);

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		if (c == '=') {
			c = getch();
			if (!islower) {
				printf("error: Invalid variable assignment\n");
				return c;
			}
			vars[c-'a'] = pop();
		} else
		return c;     /* not a number */
	i = 0;
	if (c == '-') {   /* check if - is part of a negative number */
		c = getch();
		if (c == ' ' || c == '\t' || c == '\n') { /* it's the - operator */
			ungetch(c);
			return '-';
		}
		ungetch(c);
	}
	if (isdigit(c))   /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')     /* collect fractional part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void ungets(char *s) /* push an entire string back onto the input */
{
	int i = 0;
	while (s[i] != '\0')
		i++;
	while (i > 0)
		if (bufp >= BUFSIZE) {
			printf("ungets: too many characters\n");
			return;
		} else
			buf[bufp++] = s[--i];
}

/* dabstoi:  returns the absolute value of x converted to int */
int dabstoi(double x)
{
	int i;
	i = (int) x;

	return (i >= 0) ? i : -1*i;
}

/* modulus:  calculates a % b */
double modulus(double a, double b)
{
	int ai, bi, i;

	ai = dabstoi(a);
	bi = dabstoi(b);

	if (ai > bi) {
		for (i = 1; ai >= bi*(i+1); i++)
			;
		return (b < 0) ? bi*i - ai : ai - bi*i;
	} else if (ai == bi) {
		return 0.0;
	} else {
		if (a*b > 0)
			return a;
		else
			return a + b;
	}
}

void test_ungets(void)
{
	/* test ungets */
	ungets("abc");
	printf("Test: %c\n", getch());
	printf("Test: %c\n", getch());
	printf("Test: %c\n", getch());
	printf("Pushing operation 3.141592 2 / S\n");
	ungets("3.141592 2 / S");
}
