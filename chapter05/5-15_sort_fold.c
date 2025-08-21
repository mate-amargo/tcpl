/*
 * Exercise 5-15. Add the option -f to fold upper and lower case together, so
 * that case distinctions are not made during sorting; for example, a and A
 * compare equal. □
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000     /* max #lines to be sorted */
char *lineptr[MAXLINES];  /* pointer to text lines */
int fold = 0;             /* 1 for case insensitive comparision */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void myqsort(void *lineptr[], int left, int right,
		   int (*comp)(void *, void *), int reverse);
int numcmp(const char *, const char *);
int stringcmp(const char *, const char *);

/* sort input lines */
main(int argc, char *argv[])
{
	int nlines;           /* number of input lines read */
	int numeric = 0;      /* 1 if numeric sort */
	int reverse = 0;      /* 1 for reverse order */
	int i;

	i = 1;
	while (argc > 1) {
		if (strcmp(argv[i], "-n") == 0) {
			numeric = 1;
			i++;
		} else if (strcmp(argv[i], "-r") == 0) {
			reverse = 1;
			i++;
		} else if (strcmp(argv[i], "-f") == 0) {
			fold = 1;
			i++;
		}
		argc--;
	}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		myqsort((void **) lineptr, 0, nlines-1,
		  (int (*)(void*,void*))(numeric ? numcmp : stringcmp),
		  reverse);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000   /* max length of any input line */
int getline(char *, int);
char *alloc(int);

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

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* myqsort:  sort v[left]...v[right] into increasing order or decreasing order
 * if reverse is 1 */
void myqsort(void *v[], int left, int right,
			int (*comp)(void *, void *), int reverse)
{
	int i, last;
	void swap(void *v[], int, int);
	int comparision;

	if (left >= right)   /* do nothing if array contains */
		return;          /* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++) {
		comparision = (*comp)(v[i], v[left]);
		if (reverse ? comparision > 0: comparision < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	myqsort(v, left, last-1, comp, reverse);
	myqsort(v, last+1, right, comp, reverse);
}

/* numcmp:  compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

/* lower:  returns the lowercase letter version of c */
char lower(char c)
{
	return fold && c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c;
}

/* stringcmp:  compare s1 and s2 alphabetically */
int stringcmp(const char *s1, const char *s2)
{
	for (; lower(*s1) == lower(*s2) && *s1; s1++, s2++);
	return lower(*s1) - lower(*s2);
}

/* swap:  interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
