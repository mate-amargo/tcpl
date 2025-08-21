/*
 * Exercise 5-4. Write the function strend(s,t), which returns 1 if the string
 * t occurs at the end of the string s, and zero otherwise. □
 */

#include <stdio.h>
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

int strend(char *, char *);

main()
{
	char s[] = "Aristocrat";
	char t1[] = "rat";
	char t2[] = "mouse";
	char t3[] = "e";
	char t4[] = "Aristocraticaly";

	printf("Does %s end in %s: %s\n", s, t1, strend(s, t1) ? "Yes": "No");
	printf("Does %s end in %s: %s\n", s, t2, strend(s, t2) ? "Yes": "No");
	printf("Does %s end in %s: %s\n", t2, t3, strend(t2, t3) ? "Yes": "No");
	printf("Does %s end in %s: %s\n", t2, t2, strend(t2, t2) ? "Yes": "No");
	printf("Does %s end in %s: %s\n", t3, t3, strend(t3, t3) ? "Yes": "No");
	printf("Does %s end in %s: %s\n", t2, s, strend(t2, s) ? "Yes": "No");
	printf("Does %s end in %s: %s\n", s, t4, strend(s, t4) ? "Yes": "No");
	printf("Does %s end in %s: %s\n", t4, s, strend(t4, s) ? "Yes": "No");
	return 0;
}

/* strend:  returns 1 if t occurs at the end of s, 0 otherwise */
int strend(char *s, char *t)
{
	char *head_t = t;

	while (*++s); /* walk to end of s */
	while (*++t); /* walk to end of t */
	while (*head_t != *t && *s-- == *t--); /* while they're equal rewind the ptrs */
	if (t == head_t)
		return 1;
	return 0;
}
