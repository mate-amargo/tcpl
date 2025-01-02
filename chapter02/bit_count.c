#include <stdio.h>

int bitcount(unsigned);

int main()
{
	printf("Bits in %u: %u\n", 137, bitcount(137));
	printf("Bits in %u: %u\n", 128, bitcount(128));
	printf("Bits in %u: %u\n", 8, bitcount(8));
	printf("Bits in %u: %u\n", 1, bitcount(1));
	printf("Bits in %u: %u\n", 1023, bitcount(1023));

	return 0;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
	int b;

	for (b = 0; x != 0; x >>= 1)
		if (x & 01)
			b++;
	return b;
}
