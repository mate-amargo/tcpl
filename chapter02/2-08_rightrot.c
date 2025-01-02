/*
 * Exercise 2-8. Write a function rightrot(x, n) that returns the value of the
 * integer x rotated to the right by n bit positions. □
 */

#include <stdio.h>
#include <limits.h>

unsigned short rightrot (unsigned short, unsigned short);

int main()
{
	/*   1111110000000000 */
	/*   5432109876543210 */

	/* 0b0000000000101000 = 40 */
	/* 0b0000000000010100 = 20 */
	printf("%u: %u\n", 40, rightrot(40, 1));

	/* 0b0000000000101000 = 40 */
	/* 0b0000000000001010 = 10 */
	printf("%u: %u\n", 40, rightrot(40, 2));

	/* 0b0000000000101001 = 41 */
	/* 0b1000000000010100 = 32788 */
	printf("%u: %u\n", 41, rightrot(41, 1));

	/* 0b0000000000101001 = 41 */
	/* 0b0100000000001010 =  16394 */
	printf("%u: %u\n", 41, rightrot(41, 2));

	return 0;
}

unsigned short rightrot (unsigned short x, unsigned short n)
{
	unsigned short bits = CHAR_BIT * sizeof(unsigned short);
	return (x >> n) | (x << (bits - n));
}
