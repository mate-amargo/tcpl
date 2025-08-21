/*
 * Exercise 5-10. Write the program expr, which evaluates a reverse Polish
 * expression from the command line, where each operator or operand is a
 * separate argument. For example,
 *               expr 2 3 4 + *
 * evaluates 2 x (3+4). □
 */

/*
 * Note: Using `*` for multiplication is annoying since it will be expanded by
 * the shell, unless it's quoted. This is not very comfortable, so I'll also
 * implement `x` as multiplication.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define OPERATORS 10
#define STACK_SIZE (OPERATORS*2)
#define ERROR_USAGE 1

int stackp = 0;
char ops[OPERATORS];
double stack[STACK_SIZE];

void push(double);
double pop(void);

main(int argc, char *argv[])
{
	double f;
	char ch;

	if (argc < 2) {
		printf("Usage: expr EXPRESSION\n");
		printf("For example,\n");
		printf("    expr 2 3 4 + *\n");
		printf("evaluates 2 x (3+4)\n");
		return ERROR_USAGE;
	}
	while (--argc > 0) {
		++argv;
		f = strtod(*argv, NULL);
		if (f != 0 || **argv == '0') {
			push(f);
		} else {
			ch = **argv;
			switch (ch) {
			case '+':
				push(pop()+pop());
				break;
			case '-':
				f = pop();
				push(pop() - f);
				break;
			case '*':
			case 'x':
				push(pop() * pop());
				break;
			case '/':
				f = pop();
				if (f == 0)
					printf("Error: Division by zero\n");
				else
					push(pop() / f);
				break;
			default:
				printf("Unrecognized operator\n");
			}
		}
	}
	printf("%lf\n", pop());
	return 0;
}

void push(double f)
{
	if (stackp < STACK_SIZE)
		stack[stackp++] = f;
	else
		printf("Error: stack full\n");
}

double pop(void)
{
	if (stackp > 0)
		return stack[--stackp];
	else
		printf("Error: stack empty\n");
}
