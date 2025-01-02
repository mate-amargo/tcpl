/*
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the same
 * tab stops as for detab. When either a tab or single blank would suffice to
 * reach a tab stop, which should be given preference? □
 */

#include <stdio.h>

#define TABSTOP 4


/* give preference to white space. */
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
