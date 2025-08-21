/*
 * Exercise 5-13. Write the program tail, which prints the last n lines of its
 * input. By default, n is 10, let us say, but it can be changed by an optional
 * argument, so that
 *      tail -n
 * prints the last n lines. The program should behave rationally no matter how
 * unreasonable the input or the value of n. Write the program so it makes the
 * best use of available storage; lines should be stored as in the sorting
 * program of Section 5.6, not in a two-dimensional array of fixed size. □
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000    /* max #lines to be read */
#define DEFAULT_N 10
#define MAXLEN 1000   /* max length of any input line */

char *lineptr[MAXLINES]; /* pointers to text lines */

int getline(char *, int);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int n);
char *alloc(int);
void usage(char *);

main(int argc, char *argv[])
{
	int n, nlines;

	if (argc > 2)
		usage(argv[0]);

	if (argc == 2) {
		n = -1*atoi(argv[1]);
		if (n == 0 || argv[1][0] != '-')
			usage(argv[0]);
	} else {
		n = DEFAULT_N;
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		writelines(lineptr, nlines, n);
		return 0;
	} else {
		printf("error: input too big to process\n");
		return 1;
	}

	return 0;
}

/* getline:  read a line into s, return length or -1 if read lim-1 chars */
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
#define ALLOCSIZE 1000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	} else
		return 0;
}

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines:  write last n output lines */
void writelines(char *lineptr[], int nlines, int n)
{
	int start = (nlines > n) ? nlines - n : 0;
	int i;
	for (i = start; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

void usage(char *progname)
{
	printf("Usage: %s [-n]\n", progname);
	printf("Displays the last n lines of input\n");
	printf("By default n = 10\n");
	exit(1);
}
