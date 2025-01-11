#include <stdio.h>
#include <string.h>

int trim(char []);

main()
{
	char string[] = "Hellooooo			 \n    ";
	printf("Before: \"%s\"\n", string);
	trim(string);
	printf("After: \"%s\"\n", string);
	return 0;
}

/* trim: remove trailing blanks, tabs, newlines */
int trim(char s[])
{
	int n;

	for (n = strlen(s)-1; n >= 0; n--)
		if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
			break;
	s[n+1] = '\0';
	return n;
}
