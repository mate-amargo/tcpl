#include <stdio.h>


unsigned getbits(unsigned, int, int);

int main()
{
  /*         76543210 */
  /* 237 = 0b11101101 */
  /* 237 = 0b11101101 -> (4+1-3 = 2) 011 = 3 */
  /* 237 = 0b11101101 -> (4+1-5 = 0) 11011 = 13 */
  printf("%d bits from %d in %u: %u\n", 4, 3, 237, getbits(237, 4, 3));
  printf("%d bits from %d in %u: %u\n", 4, 5, 237, getbits(237, 4, 5));
  printf("%d bits from %d in %u: %u\n", 4, 3, 253, getbits(253, 4, 3));
  printf("%d bits from %d in %u: %u\n", 4, 3, 233, getbits(233, 4, 3));
  return 0;
}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
  return (x >> (p+1-n)) & ~(~0 << n);
}
