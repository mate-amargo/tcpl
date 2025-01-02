/*
 * Exercise 2-5. Write the function any(s1,s2), which returns the first
 * location in the string s1 where any character from the string s2 occurs, or
 * -1 if s1 contains no characters from s2. (The standard library function
 *  strpbrk does the same job but returns a pointer to the location.) □
 */

#include <stdio.h>

int any(char *, char*);

int main()
{
  int pos;

  char s1[] = "Potato";
  char s2[] = "xyz";
  char s3[] = "Fox";
  printf("s1 = \"%s\"\n", s1);
  printf("s2 = \"%s\"\n", s2);
  printf("s3 = \"%s\"\n", s3);
  pos = any(s1, s2);
  if (pos < 0)
    printf("No occurrence of chars from s2 where found in s1.\n");
  else
    printf("The first location of a char from s2 in s1 is s1[%d] = %c.\n", pos, s1[pos]);
  pos = any(s3, s2);
  if (pos < 0)
    printf("No occurrence of chars from s2 where found in s3.\n");
  else
    printf("The first location of a char from s2 in s3 is s3[%d] = %c.\n", pos, s3[pos]);
  return 0;
}

int any(char *s1, char *s2)
{
  int i, j;

  for (i = 0; s1[i] != '\0'; i++) {
    for (j = 0; s2[j] != '\0'; j++) {
      if (s2[j] == s1[i]) {
        return i;
      }
    }
  }
  return -1;
}
