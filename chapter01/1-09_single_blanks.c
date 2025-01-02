/*
 * Exercise 1-9. Write a program to copy its input to its output, replacing
 * each string of one or more blanks by a single blank. □
 */

#include <stdio.h>

/* replace multiple consecutive blanks with one blank */
main()
{
  int c;

  while ((c = getchar()) != EOF) {
    putchar(c);
    if (c == ' ') {
      while ((c = getchar()) == ' ');
      putchar(c);
    }
  }
}
