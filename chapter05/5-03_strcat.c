/*
 * Exercise 5-3. Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat(s,t) copies the string t to the end of s. □
 */

#include <stdio.h>
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

void strcat(char *, char *);

main()
{
	char s[13] = "I'm a ";
	char t[] = "potato";

	strcat(s, t);
	printf("%s\n", s);
	return 0;
}

/* strcat:  concatenate t to end of s; s must be big enough */
void strcat(char *s, char *t)
{
	while (*++s); /* find end of s */
	while (*s++ = *t++); /* copy t to s */
}
