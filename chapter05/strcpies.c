#include <stdio.h>
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#define STRCPY_VER 3
#define STRCMP_VER 1

void strcpy(char *s, char *t);
int strcmp(char *s, char *t);

main()
{
	char a[256];
	char s1[] = "I'm a dog";
	char s2[] = "I'm a cat";
	int result;

	strcpy(a, "I'm a potato");
	printf("%s\n", a);
	result = strcmp(s1, s2);
	if (result < 0)
		printf("%s < %s\n", s1, s2);
	else if (result == 0)
		printf("%s == %s\n", s1, s2);
	else /* (result > 0) */
		printf("%s > %s\n", s1, s2);
	return 0;
}

#if STRCPY_VER == 0
/* strcpy: copy t to s; array subscript version */
void strcpy(char *s, char *t)
{
	int i;

	i = 0;
	while ((s[i] = t[i]) != '\0')
		i++;
}

#elif STRCPY_VER == 1
/* strcpy: copy t to s; pointer version 1 */
void strcpy(char *s, char *t)
{
	while ((*s = *t) != '\0') {
		s++;
		t++;
	}
}
#elif STRCPY_VER == 2
/* strcpy: copy t to s; pointer version 2 */
void strcpy(char *s, char *t)
{
	while ((*s++ = *t++) != '\0')
		;
}
#elif STRCPY_VER == 3
/* strcpy: copy t to s; pointer version 3 */
void strcpy(char *s, char *t)
{
	while (*s++ = *t++)
		;
}
#endif

#if STRCMP_VER == 0
/* strcmp: retun <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp(char *s, char *t)
{
	int i;

	for (i = 0; s[i] == t[i]; i++)
		if (s[i] == '\0')
			return 0;
	return s[i] - t[i];
}
#elif STRCMP_VER == 1
/* strcmp: retun <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp(char *s, char *t)
{
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}
#endif
