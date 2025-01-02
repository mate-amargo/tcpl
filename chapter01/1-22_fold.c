/*
 * Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 * □
 */

#include <stdio.h>

#define COLUMN 80


main()
{
  int i, j, k, len;
  char c;
  char buffer[COLUMN];

  i = 0; j = COLUMN;
  while ((c = getchar()) != EOF) {
    if (i < COLUMN) {
      if (c == ' ' || c == '\t') {
        j = i;
        buffer[i++] = c;
      } else if (c == '\n') {
        for (k = 0; k < i; k++)
          putchar(buffer[k]);
        putchar('\n');
        i = 0;
      } else {
        buffer[i++] = c;
      }
    } else {
      if (j == COLUMN)
        j = COLUMN -1;
      for (k = 0; k < j; k++)
        putchar(buffer[k]);
      putchar('\n');
      len = i - j -1;
      for (i = 0; i < len; i++)
        buffer[i]= buffer[j+1+i];
      i = len; j = COLUMN;
      if (c == ' ' || c == '\t') {
        j = i;
      }
      buffer[i++] = c;
    }
  }
  if (i > 0)
    for (k = 0; k < i; k++)
      putchar(buffer[k]);

  return 0;
}
