/*
 * Exercise 2-3. Write the function htoi(s), which converts a string of
 * hexadecimal digits (including an optional 0x or 0X) into its equivalent
 * integer value.  The allowable digits are 0 through 9, a through f, and A
 * through F. □
 */

#include <stdio.h>

int htoi(char *);
int hex_to_i(char);

int main()
{

	printf("Hex: %s -> Dec: %d\n", "0xa", htoi("0xa"));
	printf("Hex: %s -> Dec: %d\n", "0xFF", htoi("0xFF"));
	printf("Hex: %s -> Dec: %d\n", "0xff", htoi("0xff"));
	printf("Hex: %s -> Dec: %d\n", "0Xff", htoi("0Xff"));
	printf("Hex: %s -> Dec: %d\n", "FF", htoi("FF"));
	printf("Hex: %s -> Dec: %d\n", "0x10", htoi("0x10"));
	printf("Hex: %s -> Dec: %d\n", "0x100", htoi("0x100"));
	return 0;
}

int htoi(char *s)
{
	int i = 0, pos = 0, start = 0, h = 0, pow = 1;

	if ('\0' == s[0])
		return -1;
	if ('0' == s[0] && '\0' != s[1] && ('x' == s[1] || 'X' == s[1]))
		start = 2;

	while (s[++pos] != '\0');
	for (pos -= start; pos > 0; pos--) {
		h = hex_to_i(s[start+pos-1]);
		if (h < 0)
			return -1;
		i += pow * h;
		pow *= 16;
	}

	return i;
}

int hex_to_i(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'A' && c <= 'F')
		return 10 + c - 'A';
	else if (c >= 'a' && c <= 'f')
		return 10 + c - 'a';
	else
		return -1;
}
