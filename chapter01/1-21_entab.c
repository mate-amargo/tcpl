/*
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the same
 * tab stops as for detab. When either a tab or single blank would suffice to
 * reach a tab stop, which should be given preference? □
 */

#include <stdio.h>

#define TABSTOP 4

/* give preference to tabs. */
main()
{
	int i, c, col, spaces;

	col = 0; spaces = 0;
	while ((c = getchar()) != EOF)
		if (c == ' ') {
			spaces++;
			if ((col+spaces) % TABSTOP == 0) {
				putchar('\t');
				spaces = 0;
			}
		} else {
			while (spaces > 0) {
				putchar(' ');
				spaces--;
			}
			putchar(c);
			col = (c == '\n') ? 0 : col+1;
		}

	return 0;
}
