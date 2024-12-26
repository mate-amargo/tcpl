#include <stdio.h>
#define IN 1  /* inside  a word */
#define OUT 0 /* outside a word */
#define MAX_WORD_LENGTH 10
#define CHARS_PER_SYMBOL 5 /* How many characters means one symbol in hist */

/* Prints a histogram of the lengths of words in its input */
main()
{
  int c, state, word_length, last_c;

  /* Add 1 extra for zero length to simplify counting
   * and 1 extra for > MAX_WORD_LENGTH cases
   */
  int lengths[MAX_WORD_LENGTH + 2] = {0};

  state = IN;
  word_length = 0;
  last_c = EOF;
  while ((c = getchar()) != EOF) {
    if (state == IN && (c == ' ' || c == '\n' || c == '\t')) {
      state = OUT;
      lengths[word_length]++;
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
  if (last_c != ' ' && last_c != '\n' && last_c != '\t')
    lengths[word_length]++;

  printf("  Length   Count (# = %d)\nof words:\n", CHARS_PER_SYMBOL);
  for (c = 1; c <= MAX_WORD_LENGTH; c++) {
    printf("%8d: ", c);
    for (last_c = CHARS_PER_SYMBOL - 1; last_c < lengths[c];
         last_c += CHARS_PER_SYMBOL)
      printf("#");
    printf(" (%d)\n", lengths[c]);
  }
  printf("%7d+: ", MAX_WORD_LENGTH + 1);
  for (last_c = CHARS_PER_SYMBOL - 1; last_c < lengths[MAX_WORD_LENGTH + 1];
       last_c += CHARS_PER_SYMBOL)
    printf("#");
  printf(" (%d)\n", lengths[MAX_WORD_LENGTH + 1]);
}
