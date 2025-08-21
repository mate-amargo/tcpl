/*
 * Exercise 5-12. Extend entab and detab to accept the shorthand
 *       entab -m +n
 * to mean tab stops every n columns, starting at column m. Choose convinient
 * (for the user) default behaviour. □
 */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_M 1
#define DEFAULT_N 4

void usage(char *);

main(int argc, char *argv[])
{
	int i, c, col, m = DEFAULT_M, n = DEFAULT_N, tabstop, spaces;
	char **tabp = argv;

	if (argc > 3) {
		usage(argv[0]);
	}
	if (argc >= 2) {
		c = atoi(argv[1]);
		if (c < 0)
			m = -1*c;
		else {
			if (argv[1][0] != '+')
				usage(argv[0]);
			n = c;
		}
	}
	if (argc == 3) {
		c = atoi(argv[2]);
		if (c < 0)
			m = -1*c;
		else {
			if (argv[2][0] != '+')
				usage(argv[0]);
			n = c;
		}
	}

	col = 1; tabstop = 1; spaces = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			spaces++;
		} else {
			while (spaces > 0) {
				while (col >= m+tabstop*n)
					tabstop++;
				if (col >= m && col+spaces >= m + tabstop*n) {
					putchar('\t');
					spaces -= (m+tabstop*n - col);
					col = m + tabstop*n;
					tabstop++;
				} else {
					putchar(' ');
					spaces--;
					col++;
				}
			}
			putchar(c);
			if (c == '\n') {
				col = 1;
				tabstop = 1;
			} else {
				col++;
			}
		}
	}

	return 0;
}

void usage(char *progname)
{
	printf("%s -m +n\n", progname);
	printf("Where:\n");
	printf("\tm = Start at column m (Defaults to %d)\n", DEFAULT_M);
	printf("\tn = Tabstops every n columns (Defaults to %d)\n", DEFAULT_N);
	printf("\nExample: %s -8 +4\n", progname);
	printf("Means tabstops every four columns starting at column 8.\n");
	exit(1);
}
