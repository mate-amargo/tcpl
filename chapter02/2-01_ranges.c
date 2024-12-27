/* Write a program to determine the ranges of char, short, int, long
 * variables, both signed and unsigne, by printing appropriate values
 * from standard headers and by direct computation. Harder if you compute
 * them: determine the ranges of the various floating-point types.
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>


main()
{
  printf("unsinged\n");
  printf("  char: 0..%u\n", UCHAR_MAX);
  printf("  short int: 0..%u\n", USHRT_MAX);
  printf("  int: 0..%u\n", UINT_MAX);
  printf("  long int: 0..%lu\n", ULONG_MAX);
  printf("signed\n");
  printf("  char: %d..%d\n", SCHAR_MIN, SCHAR_MAX);
  printf("  short int: %d..%d\n", SHRT_MIN, SHRT_MAX);
  printf("  int: %d..%d\n", INT_MIN, INT_MAX);
  printf("  long int: %ld..%ld\n", LONG_MIN, LONG_MAX);
  return 0;
}
