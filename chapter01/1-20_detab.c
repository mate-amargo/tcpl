/*
 * Exercise 1-20. Write a program detab that replaces tabs in the input with
 * the proper number of blanks to space to the next tab stop. Assume a fixed
 * set of tab stops, say every n columns. Should n be a variable or a symbolic
 * parameter? □
 */

#include <stdio.h>

#define TABSTOP 4

main()
{
	int i, c, col = 0, spaces;

	while ((c = getchar()) != EOF)
		if (c == '\t') {
			spaces = TABSTOP - (col % TABSTOP);
			for (i = 0; i < spaces; i++) {
				putchar(' ');
				col++;
			}
		} else {
			putchar(c);
			col = (c == '\n') ? 0 : col+1;
		}

	return 0;
}
