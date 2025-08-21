/*
 * Exercise 5-20. Expand dcl to handle declarations with function argument
 * types, qualifiers like const, and so on. □
 */

/* TODO:
 * - [ ] fix bugs
 * - [ ] properly parse function arguments
 * - [ ] refactor
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define  MAXTOKEN   100

enum { NAME, PARENS, BRACKETS, CONST, VOLATILE, STATIC, EXTERN, AUTO, REGISTER };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char qualifier[MAXTOKEN];  /* qualifier type = const, volatile */
char storage[MAXTOKEN];  /* storage type = static, extern, auto, register */
char out[1000];           /* output string */

void error(char *);       /* error handling */

main()  /* convert declaration to words */
{
	while (gettoken() != EOF) {   /* 1st token on line */
		if (tokentype == '[' || tokentype == '(') {
			error(token);
			continue;
		}
		qualifier[0] = '\0';
		storage[0] = '\0';
		datatype[0] = '\0';
		while (tokentype == CONST || tokentype == VOLATILE ||
				tokentype == STATIC || tokentype == EXTERN ||
				tokentype == AUTO || tokentype == REGISTER) {
			if (tokentype == CONST || tokentype == VOLATILE) {
				if (qualifier[0] != '\0')
					strcat(qualifier, " ");
				strcat(qualifier, token);
			} else {
				if (storage[0] != '\0') {
					error("multiple sotrage classes");
					continue;
				}
				strcpy(storage, token);
			}
			gettoken();
		}
		strcpy(datatype, token);  /* is the datatype */
		out[0] = '\0';
		dcl();       /* parse rest of line */
		if (tokentype != '\n')
			error("syntax error");
		else if (name[0] != '\0')
			printf("%s: %s %s %s %s\n", name, storage, qualifier, out, datatype);
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
		for (*p++ = c; (c = getch()) != ')' && c != EOF && c != '\n'; )
			*p++ = c;
		if (c != ')') {
			strcpy(token, "unclosed '('");
			if (c == '\n')
				ungetch(c);
			return tokentype = '(';
		}
		*p++ = ')';
		*p = '\0';
		return tokentype = PARENS;
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
		if (strcmp(token, "const") == 0)
			return tokentype = CONST;
		else if (strcmp(token, "volatile") == 0)
			return tokentype = VOLATILE;
		else if (strcmp(token, "static") == 0)
			return tokentype = STATIC;
		else if (strcmp(token, "extern") == 0)
			return tokentype = EXTERN;
		else if (strcmp(token, "auto") == 0)
			return tokentype = AUTO;
		else if (strcmp(token, "register") == 0)
			return tokentype = REGISTER;
		else
			return tokentype = NAME;
	} else
		return tokentype = c;
}

/* dcl: parse a declarator */
void dcl(void)
{
	int ns;
	char buffer[MAXTOKEN] = "";

	for (ns = 0; gettoken() == '*'; ) {   /* count *'s */
		ns++;
		while (gettoken() == CONST || tokentype == VOLATILE) {
			if (buffer[0] != '\0')
				strcat(buffer, " ");
			strcat(buffer, token);
		}
	}

	if (tokentype == '[') {
		error(token);
		return;
	}
	if (tokentype == '(') {
		error(token);
		return;
	}

	dirdcl();
	while (ns-- > 0) {
		strcat(out, " pointer");
		if (buffer[0] != '\0') {
			strcat(out, " (");
			strcat(out, buffer);
			strcat(out, " )");
		}
		strcat(out, " to");
	}
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
	int type, len;
	char content[MAXTOKEN], *p;

	if (tokentype == NAME)    /* variable name */
		strcpy(name, token);
	else {
		error("expected name or (dcl)");
		return;
	}
	while ((type=gettoken()) == PARENS || type == BRACKETS || type == '[' || type == '(')
		if (type == '[') {
			error(token);
			return;
		} else if (type == '(') {
			error(token);
			return;
		} else if (type == PARENS) {
			strcat(out, " function ");
			strcat(out, token);
			strcat(out, " returning");
		} else {
			len = strlen(token);
			if (len > 2) {
				strncpy(content, token+1, len - 2);
				content[len-2] = '\0';
				strtol(content, &p, 10);
				if (*p != '\0') {
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
