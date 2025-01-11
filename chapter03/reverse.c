#include <stdio.h>
#include <string.h>

void reverse(char []);

main()
{
	char s[] = "My string";

	printf("Original: %s\n", s);
	reverse(s);
	printf("Reversed: %s\n", s);

	return 0;
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		/*c = s[i];*/
		/*s[i] = s[j];*/
		/*s[j] = c;*/
		/* the comma operator guarantees left to right evaluation */
		c = s[i], s[i] = s[j], s[j] = c;
	}
}
