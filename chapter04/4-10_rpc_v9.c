/*
 * Exercise 4-10. An alternate organization uses getline to read an entire
 * input line; this makes getch and ungetch unnecessary. Revise the calculator
 * to use this approach. □
 */

#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <math.h>   /* compile with -lm */
#include <string.h> /* for strcmp */

#define MAXOP           100    /* max size of operand or operator */
#define NUMBER          '0'    /* signal that a number was found */
#define PRINT_STACK      (-2)  /* singal to print the stack */
#define DUP_TOP_STACK    (-3)  /* singal to duplicate the top of the stack */
#define SWAP_TOP_STACK   (-4)  /* swap the top two elements of the stack */
#define CLEAR_STACK      (-5)  /* signal to clear the stack */
#define QUIT             (-6)  /* Quit the program. Wasn't part of ex, but fun */
#define EXP              (-7)  /* exponential function; exp(x) */
#define SIN              (-8)  /* sine of x; sin(x) */
#define COS              (-9)  /* cosine of x; cos(x) */
#define TAN             (-10)  /* tangent of x; tan(x) */
#define POW             (-11)  /* x^y; pow(x, y) */
#define ERROR          (-128)  /* error signal */
#define MAXVAL          100    /* maximum depth of val stack */
#define MAXVARS         27     /* 26 letters plus '_' for last printed value */

int sp = 0;            /* next free stack position */
double val[MAXVAL];    /* value stack */
double vars[MAXVARS];  /* The last place holds the last printed value */

int getop(char []);
void push(double);
double pop(void);
int dtoabsi(double);
double modulus(double, double);

/* reverse Polish calculator */
main()
{
	int type, i;
	double op2, op3;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case PRINT_STACK:
				if (sp == 0)
					printf("the stack is empty\n");
				else
					for (i = 0; i <= sp; i++)
						printf("%d -> %g\n", i, val[i]);
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
#define MAXLINE         126  /* max characters+1 in a line of input */

char line[MAXLINE];    /* buffer for reading input lines */
int linep = MAXLINE;   /* pointer to next readable char in line */

int getline(char [], int);

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	if (linep >= MAXLINE || line[linep] == '\0') { /* read new line */
		getline(line, MAXLINE);
		linep = 0;
	}
	if (linep == 0 && line[linep] == '\0') /* CTRL-D pressed */
		return QUIT;
	if (line[linep] == '\n') {
		linep++;
		return '\n';
	}
	/* strip whitespace */
	while (isspace(line[linep]))
		linep++;
	c = line[linep];
	i = 0;
	if (line[linep] == '=') {
		c = line[++linep];
		if (!islower) {
			printf("error: Invalid variable assignment\n");
			return ERROR;
		}
		vars[c-'a'] = pop();
		linep++;
		return c;
	}
	if (isalpha(line[linep])) {
		while (isalpha(line[linep])) {
			s[i++] = line[linep++];
		}
		if (i == 1)
			return s[0];
		s[i] = '\0';
		if      (strcmp(s, "print") == 0)
			return PRINT_STACK;
		else if (strcmp(s, "dup") == 0)
			return DUP_TOP_STACK;
		else if (strcmp(s, "swap") == 0)
			return SWAP_TOP_STACK;
		else if (strcmp(s, "clear") == 0)
			return CLEAR_STACK;
		else if (strcmp(s, "quit") == 0)
			return QUIT;
		else if (strcmp(s, "exp") == 0)
			return EXP;
		else if (strcmp(s, "sin") == 0)
			return SIN;
		else if (strcmp(s, "cos") == 0)
			return COS;
		else if (strcmp(s, "tan") == 0)
			return TAN;
		else if (strcmp(s, "pow") == 0)
			return POW;
		else {
			printf("error: Unkown command\n");
			return ERROR;
		}
	}
	if (!isdigit(c) && c != '-' && c != '.') { /* not a number */
		linep++;
		return c;
	}
	if (c == '-' && isspace(line[linep+1])) { /* subtraction */
		linep++;
		return '-';
	}
	while (!isspace(line[linep]))
		s[i++] = line[linep++];
	s[i] = '\0';
	return NUMBER;
}

/* getline: read a line into s, return length or -1 if read lim-1 chars */
int getline(char s[], int lim)
{
	int c, i;
	c = '\0';
	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return (i == lim-1)?-1:i;
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
