/*    --- detab ---
 * Replaces tabs in the input with the proper number of blanks to space
 * to the next tab stop
 */

#include <stdio.h>

#define TABSTOP 4


main()
{
  int i, c;

  while ((c = getchar()) != EOF)
    if (c == '\t')
      for (i = 0; i < TABSTOP; i++)
        printf(" ");
    else
      putchar(c);

  return 0;
}
