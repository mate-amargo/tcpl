/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters	and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapters
 * 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4). □
 */

#include <stdio.h>
#include <limits.h>
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

#define MAX_CHARS 16
#define MAX_BUFFER (MAX_CHARS+1)
#define header(func) printf("=> Testing "func"\n")

int getline(char *, int);
void itoa(int, char *);
int atoi(char *);
void strcpy(char *, char *);
void reverse(char *s);
int strrindex(char *, char *);

main()
{
	int i;
	char buf[MAX_BUFFER];

	header("getline");
	printf("Give me some input yo: ");
	i = getline(buf, MAX_BUFFER);
	printf("Read %d chars: %s\n", i < 0 ? MAX_CHARS : i, buf);

	header("itoa");
	i = 123; buf[0] = '\0';
	itoa(i, buf);
	printf("%d -> %s\n", i, buf);

	i = 2147483647; buf[0] = '\0';
	itoa(i, buf);
	printf("%d -> %s\n", i, buf);


	i = -2147483647; buf[0] = '\0';
	itoa(i, buf);
	printf("%d -> %s\n", i, buf);

	i = -2147483648; buf[0] = '\0';
	itoa(i, buf);
	printf("%d -> %s\n", i, buf);

	header("atoi");
	printf("%s -> %d\n", buf, atoi(buf));
	printf("%s -> %d\n", "  -314", atoi("  -314"));

	header("reverse");
	strcpy(buf, "My string");
	printf("Original: %s\n", buf);
	reverse(buf);
	printf("Reversed: %s\n", buf);

	header("strrindex");
	strcpy(buf, "Potatoes are good");
	printf("'Pot' in '%s' at %d\n", buf, strrindex(buf, "Pot"));
	printf("'are' in '%s' at %d\n", buf, strrindex(buf, "are"));
	printf("'good' in '%s' at %d\n", buf, strrindex(buf, "good"));

	return 0;
}

/* getline: read a line into s, return length or -1 if read lim-1 chars */
int getline(char *s, int lim)
{
	int c, i;
	c = '\0';
	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		*s++ = c;
	if (c == '\n') {
		*s++ = c;
		i++;
	}
	*s = '\0';
	return (i == lim-1)?-1:i;
}

/* itoa: convert integer n to a string s*/
void itoa(int n, char *s)
{
	int i, size;

	if (n < 0) {
		while (*s)
			s++;
		*s++ = '-';
		*s = '\0';
		if (n == INT_MIN) {  /* can't do n = -n */
			i = n; size = 1;
			while (i/10) {
				i /= 10;
				size *= 10;
			}
			i = -i;
			*s++ = i % 10 + '0'; /* add first digit */
			*s = '\0';
			n = n % size; /* chop first digit */
		}
		n = -n;          /* make n positive */
	}
	if (n / 10)
		itoa(n / 10, s);
	while (*s)
		s++;
	*s++ = n % 10 + '0';
	*s = '\0';
}

/* atoi: conver s to integer */
int atoi(char *s)
{
	int i, n, sign;

	while(isspace(*s)) /* skip white space */
		s++;
	sign = (*s == '-') ? -1: 1;
	if (*s == '+' || *s == '-') /* skip sign */
		s++;
	for (n = 0; isdigit(*s); s++)
		n = 10 * n + (*s - '0');
	return sign * n;
}

/* strcpy: copy t to s; pointer version 3 */
void strcpy(char *s, char *t)
{
	while (*s++ = *t++)
		;
}

/* reverse: reverse string s in place */
void reverse(char *s)
{
	char c;
	char *p = s;
	while (*p) /* find end of s */
		p++;
	if (! *p)
		p--;
	while (*p != *s) {
		c = *s, *s = *p, *p = c;
		p--; s++;
	}
}

/* strrindex: return index of t in s looking from the left, -1 if none */
int strrindex(char *s, char *t)
{
	int i = 0;
	char *head_t = t;
	char *current_s = s;

	while (*s) {
		current_s = s;
		t = head_t;
		while (*t == *current_s) {
			current_s++; t++;
			if (!*t)
				return i;
		}
		s++; i++;
	}
	return -1;
}
