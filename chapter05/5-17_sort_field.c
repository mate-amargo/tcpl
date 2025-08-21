/*
 * Exercise 5-17. Add a field-handling capability, so sorting may be done on
 * fields within lines, each field sorted according to an independent set of
 * options. (The index for this book was sorted with -df for the index category
 * and -n for the page numbers.) □
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000     /* max #lines to be sorted */
#define MAXFIELDS 5       /* max amount of fields to sort */
char *lineptr[MAXLINES];  /* pointer to text lines */
int fnumeric[MAXFIELDS] = {0};
int freverse[MAXFIELDS] = {0};
int ffold[MAXFIELDS] = {0};
int fdir[MAXFIELDS] = {0};
int numfields = 0;

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void myqsort(void *lineptr[], int left, int right,
		   int (*comp)(void *, void *));
int fieldcmp(const char *, const char *);
int numcmp(const char *, const char *);
int stringcmp(const char *, const char *, int, int);

/* sort input lines */
main(int argc, char *argv[])
{
	int nlines;           /* number of input lines read */
	int currentf = 0;
	int i, j;

	i = 1;
	while (argc > 1) {
		if (argv[i][0] == '-') {
			for (j = 1; argv[i][j] != '\0'; j++)
				switch(argv[i][j]) {
					case 'n': fnumeric[currentf] = 1; break;
					case 'r': freverse[currentf] = 1; break;
					case 'f': ffold[currentf] = 1; break;
					case 'd': fdir[currentf] = 1; break;
				}
			currentf++;
			numfields = currentf;
		}
		i++;
		argc--;
	}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		myqsort((void **) lineptr, 0, nlines-1,
		  (int (*)(void*,void*))fieldcmp);
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

/* myqsort:  sort v[left]...v[right] into increasing order */
void myqsort(void *v[], int left, int right,
			int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)   /* do nothing if array contains */
		return;          /* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++) {
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	myqsort(v, left, last-1, comp);
	myqsort(v, last+1, right, comp);
}

/* getfield:  returns a field from a line */
void getfield(const char *line, int fieldnum, char *dest, int maxlen)
{
	int field = 0;
	const char *start = line;
	/* skip to the desired field */
	while (field < fieldnum && *start) {
		/* skip current field */
		while (*start && *start != ' ' && *start != '\t')
			start++;
		/* skip whitespace */
		while (*start && (*start == ' ' || *start == '\t'))
			start++;
		field++;
	}
	int i = 0;
	while (i < maxlen-1 && *start && *start != ' ' && *start != '\t') {
		dest[i++] = *start++;
	}
	dest[i] = '\0';
}

/* fieldcmp:  compare s1 and s2 based on fields */
/* if (freverse[i] == 0)
 *     returns -1 if s1 < s2
 *     returns  0 if s1 == s2
 *     returns  1 if s1 > s2
 * if (freverse[i] == 1) then it's flipped
 * This results in increasing order for freverse equals 0
 *  and decreasing order for freverse equals 1
 */
int fieldcmp(const char *s1, const char *s2)
{

	if (numfields == 0) {
		return stringcmp(s1, s2, 0, 0);
	}

	int i, result;
	char field1[MAXLEN], field2[MAXLEN];
	for (i = 0; i < numfields; i ++) {
		getfield(s1, i, field1, MAXLEN);
		getfield(s2, i, field2, MAXLEN);
		if (fnumeric[i])
			result = numcmp(field1, field2);
		else
			result = stringcmp(field1, field2, fdir[i], ffold[i]);

		if (result != 0) {
			return freverse[i] ? -result : result;
		}
	}

	return 0; /* all fields are equal */
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
char lower(char c, int fold)
{
	return fold && c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c;
}

/* isdirchar:  returns 1 if the character is from the "directory set" */
int isdirchar(char c)
{
	return (c >= 'A' && c <= 'Z') ||
		   (c >= 'a' && c <= 'z') ||
		   (c >= '0' && c <= '9') ||
		   c == ' ' || c == '\t';
}

/* stringcmp:  compare s1 and s2 alphabetically */
int stringcmp(const char *s1, const char *s2, int dir, int fold)
{
	do {
		/* skips non dir chars */
		while (dir && *s1 && !isdirchar(*s1)) s1++;
		while (dir && *s2 && !isdirchar(*s2)) s2++;
		if (lower(*s1, fold) != lower(*s2, fold))
			break;
	} while (*s1++ && *s2++);
	while (dir && *s1 && !isdirchar(*s1)) s1++;
	while (dir && *s2 && !isdirchar(*s2)) s2++;

	return lower(*s1, fold) - lower(*s2, fold);
}

/* swap:  interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
