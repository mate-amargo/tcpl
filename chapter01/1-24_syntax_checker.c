/*
 * Exercise 1-24. Write a program to check a C program for rudimentary syntax
 * errors like unbalanced parentheses, brackets and braces. Don't forget about
 * quotes, both single and double quotes, escape sequences, and comments. (This
 * program is hard if you do it in full generality.) □
 */

#include <stdio.h>
#include <stdlib.h>

void error(char, char);
void unbalanced(char);
void error_comment(void);
void erase_comment(void);

main()
{
	char c;
	/*     (          [           {         "        */
	int paren = 0, bracket = 0, brace = 0, doubl = 0;

	while ((c = getchar()) != EOF) {
		if (c == '/') {
			c = getchar();
			if (c == EOF)
				error_comment();
			if (c == '*') /* we are inside a comment */
				erase_comment();
		} else if (c == '\'') {
			c = getchar();
			if (c == EOF)
				error('\'', c);
			else if (c == '\\') {
				c = getchar();
				if (c == EOF)
					error('\'', c);
				c = getchar();
				if (c != '\'')
					error('\'', c);
			} else {
				c = getchar();
				if (c != '\'')
					error('\'', c);
			}
		} else if (!doubl) {
			if (c == '"')
				doubl ^= 1;
			else if (c == '(')
				paren += 1;
			else if (c == '[')
				bracket += 1;
			else if (c == '{')
				brace += 1;
			else if (c == ')') {
				paren--;
				if (paren < 0)
					unbalanced('(');
			} else if (c == ']') {
				bracket--;
				if (bracket < 0)
					unbalanced('[');
			} else if (c == '}') {
				brace--;
				if (brace < 0)
					unbalanced('{');
			}
		}
	}
	printf("Syntax OK :)\n");
	exit(EXIT_SUCCESS);
}

void error(char expected, char actual)
{
	printf("Unmatched character. Expected %c. Got %c\n", expected, actual);
	exit(EXIT_FAILURE);
}

void unbalanced(char expected)
{
	printf("Unmatched %c\n", expected);
	exit(EXIT_FAILURE);
}

void error_comment(void)
{
	printf("Comment not closed\n");
	exit(EXIT_FAILURE);
}

void erase_comment(void)
{
	char c;

	while ((c = getchar()) != EOF) {
		if (c == '*') { /* *marks potential ending */
			c = getchar();
			if (c == EOF)
				error_comment();
			if (c == '/') /* finishing slash, end comment */
				break;
		}
	}
	/* check that we ended the while loop by finishing the comment */
	if (c == EOF)
		error_comment();
	c = getchar();
	if (c == EOF)
		/* in this case we end in success since this case marks a
		 * file finishing in a comment
		 */
		exit(EXIT_SUCCESS);
}
