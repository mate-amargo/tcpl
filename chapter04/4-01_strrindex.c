/*
 * Exercise 4-1. Write the function strrindex(s,t), which returns the position
 * of the rightmost occurrence of t in s, or -1 if there is none. □
 */

#include <stdio.h>
#include <string.h>
#define MAXLINE 1000 /* maximum input line length */

int getline(char line[], int max);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould"; /* pattern to search for */

/* find all lines matching pattern */
main()
{
	char line[MAXLINE];
	int found = 0;
	int pos = -1;

	while (getline(line, MAXLINE) > 0)
		if ((pos = strrindex(line, pattern)) >= 0) {
			printf("%d: %s", pos, line);
			found ++;
		}
	return found;
}

/* getline: get line into s, return length */
int getline(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* strrindex: return index of t in s looking from the right, -1 if none */
int strrindex(char s[], char t[])
{
	int i, j, k;

	for (i = strlen(s)-1; i > 0; i--) {
		for (j=i, k=strlen(t)-1; k > 0 && s[j]==t[k]; j--, k--)
			;
		if (k == 0)
			return j;
	}
	return -1;
}
