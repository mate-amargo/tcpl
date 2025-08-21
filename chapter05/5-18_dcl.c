/*
 * Exercise 5-18. Make dcl recover from input errors. □
 */

/*
 * The books says:
 *   "Since programs are intented to be illustrative, not bullet-proof, there
 *   are significant restrictions on dcl. It can only handle a simple data type
 *   like char or int. It does not handle argument types in functions, or
 *   qualifiers like const. Spurious blanks confuse it. It doesn't do much
 *   error recovery, so invalid declarations will also confuse it. These
 *   improvements are left as exercises."
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define  MAXTOKEN   100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[1000];           /* output string */

void error(char *);       /* error handling */

main()  /* convert declaration to words */
{
	while (gettoken() != EOF) {   /* 1st token on line */
		if (tokentype == '[') {
			error(token);
			continue;
		}
		strcpy(datatype, token);  /* is the datatype */
		out[0] = '\0';
		dcl();       /* parse rest of line */
		if (tokentype != '\n')
			error("syntax error");
		else if (name[0] != '\0')
			printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}

void error(char *msg)
{
	printf("error: %s\n", msg);
	while (tokentype != '\n' && tokentype != EOF)
		gettoken();
	out[0] = '\0';
	name[0] = '\0';
}

int gettoken(void)  /* return next token */
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;
	char *end;

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (c = getch()) != ']' && c != EOF && c != '\n'; )
			*p++ = c;
		if (c != ']') {
			strcpy(token, "unclosed '['");
			if (c == '\n')
				ungetch(c);
			return tokentype = '[';
		}
		*p++ = ']';
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}

/* dcl: parse a declarator */
void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; )    /* count *'s */
		ns++;

	if (tokentype == '[') {
		error(token);
		return;
	}

	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to ");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
	int type, len;
	char content[MAXTOKEN], *end;

	if (tokentype == '(') {          /* ( dcl ) */
		dcl();
		if (tokentype != ')') {
			error("missing )");
			return;
		}
	} else if (tokentype == NAME)    /* variable name */
		strcpy(name, token);
	else {
		error("expected name or (dcl)");
		return;
	}
	while ((type=gettoken()) == PARENS || type == BRACKETS || type == '[')
		if (type == '[') {
			error(token);
			return;
		} else if (type == PARENS)
			strcat(out, " function returning");
		else {
			len = strlen(token);
			if (len > 2) {
				strncpy(content, token+1, len - 2);
				content[len-2] = '\0';
				strtol(content, &end, 10);
				if (*end != '\0') {
					strcpy(token, "invalid array size");
					error(token);
					return;
				}
			}
			strcat(out, " array ");
			strcat(out, token);
			strcat(out, " of ");
		}
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
	int c;
	while (1) {
		c = (bufp > 0) ? buf[--bufp] : getchar();
		if (c != EOF)
			return c;
	}
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
