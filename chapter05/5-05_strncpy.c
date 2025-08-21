/*
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B. □
 */

#include <stdio.h>
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

#define MAX_BUFFER 256

void strncpy(char *, char *, int);
void strncat(char *, char *, int);
int strncmp(char *, char *, int);

main()
{

	char s[MAX_BUFFER];
	char t[] = "Potato";
	char t2[] = "teryl";
	int n, result;

	printf("Before copying\n");
	printf("%s -> %s\n", t, s);
	n = 3;
	printf("After copying %d characters from t to s\n", n);
	strncpy(s, t, n);
	printf("%s -> %s\n", t, s);
	n = 4;
	printf("Appending first %d chars from %s to the end of %s\n", n, t2, s);
	strncat(s, t2, n);
	printf("%s\n", s);
	n = 3;
	result = strncmp(s, t, n);
	if (result < 0)
		printf("First %d chars: %s < %s\n", n, s, t);
	else if (result == 0)
		printf("First %d chars: %s == %s\n", n, s, t);
	else /* (result > 0) */
		printf("First %d chars: %s > %s\n", n, s, t);
	return 0;
}

/* strncpy:  copies n characters from t to s */
void strncpy(char *s, char *t, int n)
{
	int i;

	for (i = 0; i < n; i++)
		*s++ = *t++;
}

/* strncat:  concatenate n chars from the string t to the end of s*/
void strncat(char *s, char *t, int n)
{
	int i;
	while (*++s); /* find end of s */
	for (i = 0; i < n; i++)
		*s++ = *t++;
}

/* strncmp:  compare at most n chars from s and t, returns 0 if equal, a
 * negative number if s < t, or a positive number if s > t
 */
int strncmp(char *s, char *t, int n)
{
	int i;
	for (i = 0; i < n; s++, t++, i++)
		if (*s != *t)
			return *s - *t;
	return 0;
}
