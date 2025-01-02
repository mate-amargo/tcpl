/*
 * Exercise 2-4. Write an alternate version of squeeze(s1, s2) that deletes
 * each charcter in s1 that matches any character in the string s2. □
 */

#include <stdio.h>

void squeeze(char *, char*);

int main()
{
	char s1[] = "I like cats and dogs, what about you?";
	char s2[] = "aeiou";
	printf("s1 = \"%s\"\n", s1);
	printf("s2 = \"%s\"\n", s2);
	printf("Squeezing...\n");
	squeeze(s1, s2);
	printf("s1 = \"%s\"\n", s1);
	printf("s2 = \"%s\"\n", s2);
	return 0;
}

void squeeze(char *s1, char *s2)
{
	int i, j, k, c_in_s1 = 0;

	for (i = k = 0; s1[i] != '\0'; i++) {
		for (j = 0; s2[j] != '\0'; j++) {
			if (s2[j] == s1[i]) {
				c_in_s1 = 1;
				break;
			}
		}
		if (c_in_s1)
			c_in_s1 = 0;
		else
			s1[k++] = s1[i];
	}
	s1[k] = '\0';
}
