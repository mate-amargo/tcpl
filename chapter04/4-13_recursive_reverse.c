/*
 * Exercise 4-13. Write a recursive version of the function reverse(s), which
 * reverses the string s in place. □
 */

#include <stdio.h>
#include <string.h>

#define BUFFER 512

void reverse(char []);
void reverse_swap(char [], int, int);

main()
{
	int i;
	char a[BUFFER];

	strcpy(a, "I'm a potato");
	printf("%s -> ", a);
	reverse(a);
	printf("%s\n", a);

	strcpy(a, "cat");
	printf("%s -> ", a);
	reverse(a);
	printf("%s\n", a);

	strcpy(a, "dogs");
	printf("%s -> ", a);
	reverse(a);
	printf("%s\n", a);

	strcpy(a, "1");
	printf("%s -> ", a);
	reverse(a);
	printf("%s\n", a);

	strcpy(a, "A man a plan a canal Panama");
	printf("%s -> ", a);
	reverse(a);
	printf("%s\n", a);

	return 0;
}

/* reverse_swap: recursive part where the swapping happens */
void reverse_swap(char s[], int i, int j)
{
	char c;
	if (i <= j) {
		c = s[i], s[i] = s[j], s[j] = c;
		reverse_swap(s, i+1, j-1);
	}
}

/* reverse: reverse a string s in place of length n (not counting '\0') */
void reverse(char s[])
{
	int len;
	len = strlen(s);
	reverse_swap(s, 0, len-1);
}
