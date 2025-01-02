/*
 * Exercise 1-23. Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly. C
 * comments do not nest. □
 */

#include <stdio.h>
#include <stdlib.h>

void erase_comment(void);
void check_not_EOF(char);

/* This program removes C-style comments from a C program.
 * I'll try to do this without reading line by line, but rather
 * character by character.
 * TODO: Right now a comment standing on its own line (either proceeded
 * or succeeded by whitespace produces a visually empty line
 * (technically it's not empty since it will have whitespace). Try
 * to completely remove such lines.
 */
main()
{
  char c;

  while ((c = getchar()) != EOF) {
    if (c == '/') {
      c = getchar();
      check_not_EOF(c);
      if (c == '*') /* we are inside a comment */
        erase_comment();
      else
        printf("/%c", c);
    } else {
      putchar(c);
    }
  }

  exit(EXIT_SUCCESS);
}

void erase_comment(void)
{
  char c;

  while ((c = getchar()) != EOF) {
    if (c == '*') { /* *marks potential ending */
      c = getchar();
      check_not_EOF(c);
      if (c == '/') /* finishing slash, end comment */
        break;
    }
  }
  /* check that we ended the while loop by finishing the comment */
  check_not_EOF(c);
  c = getchar();
  if (c == EOF)
    /* in this case we end in success since this case marks a
     * file finishing in a comment
     */
    exit(EXIT_SUCCESS);
  putchar(c);
}

void check_not_EOF(char c)
{
  if (c == EOF)
    /* we got to EOF before finishing the comment */
    exit(EXIT_FAILURE);
}
