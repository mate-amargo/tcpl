/*
 * Exercise 1-18. Write a program to remove trailing blanks and tabs from each
 * line of input, and to delete entirely blank lines. □
 */

#include <stdio.h>
#define MAXCHARS 125
#define MAXLINE (MAXCHARS+1) /* maximum input line size plus \0 */

/* Remove trailing blanks and tabs from each line of input, and delete entirely blank lines */

int getline(char line[], int maxline);
void trimline(char line[], int length);

main()
{
  int len;
  char buffer[MAXLINE];

  while ((len = getline(buffer, MAXLINE)) != 0) {
    trimline(buffer, len);
    printf("%s", buffer);
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

/* trimline: trims trailing blanks and tabs from the end */
void trimline(char line[], int length)
{
  int i;
  i = length-2; /* skip "\n\0" */
  while (i > 0 && (line[i] == ' ' || line[i] == '\t')) {
    --i;
  }
  line[++i] = '\n';
  line[++i] = '\0';
}
