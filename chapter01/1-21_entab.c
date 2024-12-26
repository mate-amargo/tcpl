/*    --- entab ---
 * Replaces strings of blank spaces with the minimum number of tabs
 * to achieve the same spacing. Uses same TABSTOP as detab.
 * When either a tab or single blank would suffice to reach a tab stop
 * give preference to white space.
 */

#include <stdio.h>

#define TABSTOP 4


main()
{
  int i, j, c;
  char buffer[TABSTOP-1];

  i = 0;
  while ((c = getchar()) != EOF)
    if (c == ' ') {
      if (i < TABSTOP-1)
        buffer[i++] = c;
      else {
        putchar('\t');
        i = 0;
      }
    } else {
      if (i > 0){
        for (j = 0; j < i; j++)
          putchar(buffer[j]);
        i = 0;
      }
      putchar(c);
    }

  return 0;
}
