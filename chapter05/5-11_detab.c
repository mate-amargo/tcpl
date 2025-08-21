/*
 * Exercise 5-11. Modify the programs entab and detab (written as exercises in
 * Chapter 1) to accept a list of tab stops as arguments. Use the default tab
 * settings if there are no arguments. □
 */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_TO_SPACES 4

main(int argc, char *argv[])
{
	int i, c, col, tabs, tabstop;
	char **tabp = argv;

	col = 1; tabstop = 0; tabs = argc - 1;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			if (tabs > 0) {
				while (col >= tabstop && tabs > 0) {
					tabstop = atoi(*++tabp);
					tabs--;
				}
				for (; col < tabstop; col++) {
					putchar(' ');
				}
			} else {
				for (i = 0; i < DEFAULT_TAB_TO_SPACES; i++) {
					putchar(' ');
					col++;
				}
			}
		} else {
			putchar(c);
			if (c == '\n') {
				col = 1;
				tabs = argc - 1;
				tabp = argv;
				tabstop = 0;
			} else {
				col++;
			}
		}
	}

	return 0;
}
