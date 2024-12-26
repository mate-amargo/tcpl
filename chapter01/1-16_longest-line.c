#include <stdio.h>
#define MAXCHARS 120
#define MAXLINE (MAXCHARS+1) /* maximum input line size plus \0 */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
main()
{
  int len; /* current line length */
  int max; /* maximum length seen so far */
  char line[MAXLINE]; /* current input line */
  char longest[MAXLINE]; /* longest line saved here */

  max = 0;
  while ((len = getline(line, MAXLINE)) != 0)
    if (len == -1) {
      if (max < MAXCHARS)
        copy(longest, line);
      max += MAXCHARS;
    } else if (len > max) {
      max = len;
      copy(longest, line);
    }
  if (max > 0) /* there was a line */
    printf("Maximum length: %d\nLine (up to %d characters):\n%s", max, MAXCHARS, longest);
  return 0;
}

/* getline: read a line into s, return length or -1 if read lim-1 chars */
int getline(char s[], int lim)
{
  int c, i;
  c = '\0';
  for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return (i == lim-1)?-1:i;
}

/* copy: copoy `from` into `to`; assume to is big enough */
void copy(char to[], char from[])
{
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
