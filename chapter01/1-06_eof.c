#include <stdio.h>

main()
{
  int c;

  c = getchar() != EOF; /* equivalent to c = (getchar() != EOF) */
  printf("getchar() != EOF is %d\n", c);
}
