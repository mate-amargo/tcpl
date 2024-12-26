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
