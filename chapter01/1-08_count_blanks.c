/*
 * Exercise 1-8. Write a program to count blanks, tabs, and newlines. □
 */

#include <stdio.h>

/* count blanks, tabs and newlines in input */
main()
{
	int c, nl, blank, tab;

	nl = blank = tab = 0;
	while ((c = getchar()) != EOF)
		if (c == '\n')
			++nl;
		else if (c == ' ')
			++blank;
		else if (c == '\t')
			++tab;
	printf("New lines: %d\n", nl);
	printf("Blanks: %d\n", blank);
	printf("Tabs: %d\n", tab);
}
