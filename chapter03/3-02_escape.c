/*
 * Exercise 3-2. Write a function escape(s, t) that converts characters like
 * newline and tab into visible escape sequences line \n and \t as it copies
 * the string t to s. Use a switch. Write a funtion for the other direction as
 * well, converting escape sequences into real characters. □
 */

#include <stdio.h>

#define BUFFER  256

void escape(char *, char *);
void unescape(char *, char *);

main()
{
	char original[] = "I'm a potato\twith eyes\nWhat up?!";
	char escaped[BUFFER];
	char recovered[BUFFER];

	printf("Original  string: \"%s\"\n", original);

	escape(original, escaped);
	printf("Escaped   string: \"%s\"\n", escaped);

	unescape(escaped, recovered);
	printf("Recovered string: \"%s\"\n", recovered);

	return 0;
}

/* escape: copies s to t, escaping whitespace characters */
void escape(char *s, char *t)
{
	/* Particularly, it converts:
	 * Tab      to   '\t'
	 * Newline  to   '\n'
	 * space    to   '\ '
	 */
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++)
		switch (s[i]) {
			case ' ':
				t[j++] = '\\';
				t[j++] = ' ';
				break;
			case '\t':
				t[j++] = '\\';
				t[j++] = 't';
				break;
			case '\n':
				t[j++] = '\\';
				t[j++] = 'n';
				break;
			default:
				t[j++] = s[i];
				break;
		}
}

/* unescape: copies s to t, converting scaped whitespace to chars */
void unescape(char *s, char *t)
{
	/* Particularly, it converts:
	 * '\t'  to   Tab
	 * '\n'  to   Newline
	 * '\ '  to   space
	 */
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++)
		if (s[i] == '\\') {
			i++;
			switch (s[i]) {
				case ' ':
					t[j++] = ' ';
					break;
				case 't':
					t[j++] = '\t';
					break;
				case 'n':
					t[j++] = '\n';
					break;
				default:
					t[j++] = '\\';
					t[j++] = s[i];
					break;
			}
		} else
			t[j++] = s[i];
}
