/*
 * Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the
 * rightmost 1-bit in x. Explain why. Use this observation to write a faster
 * version of bitcount. □
 */


/*
 * Explanation:
 * In two's complement the MSB (Most Significant Bit) indicates the sign:
 * MSB = 0 -> Positive.
 * MSB = 1 -> Negative.
 *
 *   00001010 (10)
 * & 00001001 (09)
 *   --------
 *   00001000
 *
 *   11111010 (-6)
 * & 11111001 (-7)
 *   --------
 *   11111000
 *
 *
 *   11110000 (-16)
 * & 11101111 (-17)
 *   --------
 *   11100000
 *
 * So in two's complement, doing x-1 flips the rightmost 1-bit of x and also
 * all the rest of the bits to its right get fliped. Therefore, when doing an
 * AND between x and x-1 the result is that the rightmost 1-bit of x gets
 * deleted, i.e. set to zero.
 */

#include <stdio.h>

int bitcount(unsigned);

int main()
{
  printf("Bits in %u: %u\n", 137, bitcount(137));
  printf("Bits in %u: %u\n", 128, bitcount(128));
  printf("Bits in %u: %u\n", 8, bitcount(8));
  printf("Bits in %u: %u\n", 1, bitcount(1));
  printf("Bits in %u: %u\n", 1023, bitcount(1023));
  printf("Bits in %u: %u\n", 1, bitcount(1));
  printf("Bits in %u: %u\n", 2, bitcount(2));
  printf("Bits in %u: %u\n", 17, bitcount(17));

  return 0;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
  int b;

  for (b = 0; x != 0; x &= (x-1))
    b++;
  return b;
}
