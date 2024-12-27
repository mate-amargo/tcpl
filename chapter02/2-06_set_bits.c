/*
 * Write a function setbits(x,p,n,y) that returs x with the n bits that begin at
 * position p set to the rightmost n bits of y, leaving the other bits unchanged
 */

#include <stdio.h>


unsigned setbits(unsigned, int, int, unsigned);

int main()
{
  /*   76543210 */

  /* 0b00111000 = 56 */
  /* 0b11010010 = 210 */
  /* 0b00010000 = 16 */
  printf("%u: %u\n", 56, setbits(56, 5, 3, 210));

  /* 0b00111000 = 56 */
  /* 0b11010100 = 212 */
  /* 0b00100000 = 32 */
  printf("%u: %u\n", 56, setbits(56, 5, 3, 212));

  /* 0b10111000 = 184 */
  /* 0b11010010 = 210 */
  /* 0b10010000 = 144 */
  printf("%u: %u\n", 184, setbits(184, 5, 3, 210));

  /* 0b10111000 = 184 */
  /* 0b11010100 = 212 */
  /* 0b10100000 = 160 */
  printf("%u: %u\n", 184, setbits(184, 5, 3, 212));

  return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  return ( x & ~((~0 << (p+1-n)) ^ (~0 << (p+1))) ) | ((y & ~(~0 << n)) << (p+1-n));
}
