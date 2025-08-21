/*
 * Exercise 5-11. Modify the programs entab and detab (written as exercises in
 * Chapter 1) to accept a list of tab stops as arguments. Use the default tab
 * settings if there are no arguments. □
 */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SPACES_TO_TABS 4

/* give preference to tabs. */
main(int argc, char *argv[])
{
	int i, c, col, spaces, tabs, tabstop;
	char **tabp = argv;

	col = 1; spaces = 0; tabs = argc - 1; tabstop = DEFAULT_SPACES_TO_TABS;
	if (tabs > 0) {
		tabstop = atoi(*++tabp);
		tabs--;
	}
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			spaces++;
		} else {
			while (spaces > 0) {
				if ((col+spaces) >= tabstop) {
					putchar('\t');
					spaces = col+spaces - tabstop;
					col = tabstop;
					if (tabs > 0) {
						tabstop = atoi(*++tabp);
						tabs--;
					} else {
						tabstop += DEFAULT_SPACES_TO_TABS;
					}
				} else {
					putchar(' ');
					spaces--;
				}
			}
			putchar(c);
			if (c == '\n') {
				col = 1;
				tabs = argc - 1;
				tabp = argv;
				if (tabs > 0) {
					tabstop = atoi(*++tabp);
				} else {
					tabstop = DEFAULT_SPACES_TO_TABS;
				}
				tabs--;
			} else {
				col++;
			}
		}
	}

	return 0;
}
