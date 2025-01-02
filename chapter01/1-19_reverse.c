/*
 * Exercise 1-19. Write a function reverse(s) that reverses the character
 * string s. Use it to write a program that reverses its input a line at a
 * time. □
 */

#include <stdio.h>
#define MAXCHARS 81

/* reverse*/
main()
{
  int pos = 0; /* current position in the stack */
  char c;
  char stack[MAXCHARS]; /* stack to hold input chars */

  while ((c = getchar()) != EOF) {
    if (pos > MAXCHARS) {
      printf("Maximum input line exceeded (%d)\n", MAXCHARS);
      return 1;
    }
    if (c == '\n') {
      while (pos >= 0)
        printf("%c", stack[pos--]);
      printf("\n");
      pos = 0;
    } else
      stack[pos++] = c;
  }
  return 0;
}
