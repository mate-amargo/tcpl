/*
 * Exercise 1-17. Write a program to print all input lines that are longer than
 * 80 characters. □
 */

#include <stdio.h>
#define MAXCHARS 81
#define MAXLINE (MAXCHARS+1) /* maximum input line size plus \0 */

int getline(char line[], int maxline);

/* print lines that are longer than 80 characters */
main()
{
  int len; /* current line length */
  char buffer[MAXLINE]; /* current input line */

  while ((len = getline(buffer, MAXLINE)) != 0)
    if (len == -1) {
      printf("%s", buffer);
      if (buffer[MAXCHARS-1] != '\n') {
        len = getline(buffer, MAXLINE);
        if (len == 0)
          break;
        else
          printf("%s", buffer);
      }
    }
  return 0;
}

/* getline: read a line into s, return length or -1 if read lim-1 chars */
int getline(char s[], int lim)
{
  int c, i;
  for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return (i == lim-1)?-1:i;
}
