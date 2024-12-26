#include <stdio.h>
#define IN 1  /* inside  a word */
#define OUT 0 /* outside a word */
#define MAX_WORD_LENGTH 15
#define CHARS_PER_SYMBOL 5 /* How many characters means one symbol in hist */

/* Prints a histogram of the lengths of words in its input */
/* Vertical version */
main()
{
  int c, state, word_length, last_c, max_count;

  /* Add 1 extra for zero length to simplify counting
   * and 1 extra for > MAX_WORD_LENGTH cases
   */
  int lengths[MAX_WORD_LENGTH + 2] = {0};

  state = IN;
  word_length = 0;
  max_count = 0;
  last_c = EOF;
  while ((c = getchar()) != EOF) {
    if (state == IN && (c == ' ' || c == '\n' || c == '\t')) {
      state = OUT;
      lengths[word_length]++;
      if (lengths[word_length] > max_count)
        max_count = lengths[word_length];
      word_length = 1;
      last_c = c;
    } else if (state == OUT && c != ' ' && c != '\n' && c != '\t') {
      state = IN;
    } else if (c != ' ' && c != '\n' && c != '\t' &&
               word_length <= MAX_WORD_LENGTH) {
      word_length++;
    }
  }
  /* if the input doesn't end with blank keep track of the last */
  if (last_c != ' ' && last_c != '\n' && last_c != '\t') {
    lengths[word_length]++;
    if (lengths[word_length] > max_count)
      max_count = lengths[word_length];
  }
  for (state = max_count / CHARS_PER_SYMBOL; state >= 0; state--) {
    for (c = 1; c <= MAX_WORD_LENGTH + 1; c++) {
      if (state == lengths[c] / CHARS_PER_SYMBOL)
        printf(" (%2d)", lengths[c]);
      else if (state > lengths[c] / CHARS_PER_SYMBOL)
        printf("     ");
      else
        printf("  #  ");
    }
    printf("\n");
  }
  for (c = 1; c <= MAX_WORD_LENGTH + 1; c++)
    printf("-----");
  printf("\n");
  for (c = 1; c <= MAX_WORD_LENGTH; c++)
    printf(" %3d ", c);
  printf(" %3d+\n", MAX_WORD_LENGTH+1);
}
