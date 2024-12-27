/*
 * Rewrite the functinon lower, which converts upper case letters to
 * lower case, with a conditional expression instead of an if-else.
 */

#include <stdio.h>

int lower(int);

int main()
{

  char *myText = "I'm a BIG Potato";
  int i;

  for (i = 0; myText[i] != '\0'; i++)
    printf("%c", lower(myText[i]));

  putchar('\n');

  return 0;
}

int lower(int c)
{
  return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
