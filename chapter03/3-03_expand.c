/*
 * Exercise 3-3. Write a function expand(s1, s2) that expands shorthand
 * notation like a-z in the string s1 into the equivalent complete list
 * abc...xyz in s2. Allow for letters of either case and digits, and be
 * prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a
 * leading or trailing - is taken literally. □
 */

#include <stdio.h>
#include <ctype.h>

#define BUFFER  512

void expand(char *, char *);
char israngeable(char);

main()
{
	char shorthand_1[] = "This is a range a-z cool eh?";
	char shorthand_2[] = "What about -a-n";
	char shorthand_3[] = "And a-b-c";
	char shorthand_4[] = "rot13: A-Za-z N-ZA-Mn-za-m";
	char shorthand_5[] = "bash -- -l";
	char shorthand_6[] = "And a trailing dash-";
	char shorthand_7[] = "Numbers? 0-9 or 3-7 is it ok?";
	char expanded[BUFFER];

	expand(shorthand_1, expanded);
	printf("Original: %s\nExpanded: %s\n------\n", shorthand_1, expanded);
	expand(shorthand_2, expanded);
	printf("Original: %s\nExpanded: %s\n------\n", shorthand_2, expanded);
	expand(shorthand_3, expanded);
	printf("Original: %s\nExpanded: %s\n------\n", shorthand_3, expanded);
	expand(shorthand_4, expanded);
	printf("Original: %s\nExpanded: %s\n------\n", shorthand_4, expanded);
	expand(shorthand_5, expanded);
	printf("Original: %s\nExpanded: %s\n------\n", shorthand_5, expanded);
	expand(shorthand_6, expanded);
	printf("Original: %s\nExpanded: %s\n------\n", shorthand_6, expanded);
	expand(shorthand_7, expanded);
	printf("Original: %s\nExpanded: %s\n------\n", shorthand_7, expanded);

	return 0;
}

char israngeable(char c) {
	if (isalpha(c) || isdigit(c))
		return 1;
	return 0;
}

void expand(char *s1, char *s2)
{
	int i, j, k;

	for (i = 0, j = 0; s1[i] != '\0';) {
		if (s1[i+1] == '-' && israngeable(s1[i+2]) && israngeable(s1[i])) {
			for (k = s1[i]; k <= s1[i+2]; k++) {
				s2[j++] = k;
			}
			i += 3;
		} else
			s2[j++] = s1[i++];
	}

	s2[j] = '\0';
}
