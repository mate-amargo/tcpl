/*
 * Exercise 2-7. Write a function invert(x, p, n) that returns x with the n
 * bits that begin at position p inverted (i.e., 1 changed into 0 and vice
 * versa), leaving the others unchanged. □
 */

#include <stdio.h>

unsigned invert (unsigned, int, int);

int main()
{
  /*   76543210 */

  /* 0b00101000 = 40 */
  /* 0b00010000 = 16 */
  printf("%u: %u\n", 40, invert(40, 5, 3));

  /* 0b10101001 = 169 */
  /* 0b10010001 = 145 */
  printf("%u: %u\n", 169, invert(169, 5, 3));

  /* 0b10101001 = 169 */
  /* 0b10101110 = 174 */
  printf("%u: %u\n", 169, invert(169, 2, 3));

  /* 0b00101000 = 40 */
  /* 0b11001000 = 200 */
  printf("%u: %u\n", 40, invert(40, 7, 3));

  return 0;
}

unsigned invert (unsigned x, int p, int n)
{
  return (
    (x & ~((~0 << (p+1-n)) ^ (~0 << (p+1))))
    | ( (x & ((~0 << (p+1-n)) ^ (~0 << (p+1))))
      ^ ((~0 << (p+1-n)) ^ (~0 << (p+1)))
      )
  );
}
