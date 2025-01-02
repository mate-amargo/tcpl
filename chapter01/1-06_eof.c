/*
 * Exercise 1-6. Verify that the expression getchar() != EOF is 0 or 1. □
 */

#include <stdio.h>

main()
{
  int c;

  c = getchar() != EOF; /* equivalent to c = (getchar() != EOF) */
  printf("getchar() != EOF is %d\n", c);
}
