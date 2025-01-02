/*
 * Exercise 1-14. Write a program to print a histogram of the frequencies of
 * different characters in its input. □
 */

#include <stdio.h>
#define START_CHAR ' '
#define END_CHAR   '~'
#define MAX_CHARS (END_CHAR - START_CHAR + 2) /* Range of chars + 1 for other*/
#define CHARS_PER_SYMBOL 5 /* How many characters means one symbol in hist */

/* Prints a histogram of the frequency of chars in its input */
main()
{
	int c, max;

	int freq[MAX_CHARS] = {0};
	max = 0;

	while ((c = getchar()) != EOF) {
		if (c < START_CHAR || c > END_CHAR) {
			++freq[MAX_CHARS-1];
		}
		else {
			++freq[c - START_CHAR];
		}
		if (c > max)
			max = c;
	}
	printf("Frequency   Count (# = %d)\n of char:\n", CHARS_PER_SYMBOL);
	for (c = 0; c < MAX_CHARS-1; c++) {
		printf("%8c: ", START_CHAR + c);
		for (max = CHARS_PER_SYMBOL - 1; max < freq[c]; max += CHARS_PER_SYMBOL)
			printf("#");
		printf(" (%d)\n", freq[c]);
	}
	printf("   Other: ");
	for (max = CHARS_PER_SYMBOL - 1; max < freq[MAX_CHARS-1];
			max += CHARS_PER_SYMBOL)
		printf("#");
	printf(" (%d)\n", freq[MAX_CHARS-1]);
}
