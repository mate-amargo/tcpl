#!/bin/bash
# Exercise 1-11. How would you test the word cound program? What kinds of input
# are most likely to uncover bugs if there are any? □

INPUTS=(
"1 "
"2\n"
"3"
"\n"
" \n \n"
""
" "
)

for input in "${INPUTS[@]}"; do
  SIMPLE_WC=$(echo -en "${input}" | ./simple_wc)
  SIMPLE_WC_LINES=$(echo $SIMPLE_WC | cut -d ' ' -f1)
  SIMPLE_WC_WORDS=$(echo $SIMPLE_WC | cut -d ' ' -f2)
  SIMPLE_WC_CHARACTERS=$(echo $SIMPLE_WC | cut -d ' ' -f3)
  WC_LINES=$(echo -en "${input}" | wc -l)
  WC_WORDS=$(echo -en "${input}" | wc -w)
  WC_CHARACTERS=$(echo -en "${input}" | wc -m)
  if [ "${SIMPLE_WC_LINES}" -eq "${WC_LINES}" ]; then
    echo Lines OK
  else
    echo Lines WRONG
    exit 1
  fi
  if [ "${SIMPLE_WC_WORDS}" -eq "${WC_WORDS}" ]; then
    echo Words OK
  else
    echo Words WRONG
    exit 1
  fi
  if [ "${SIMPLE_WC_CHARACTERS}" -eq "${WC_CHARACTERS}" ]; then
    echo Characters OK
  else
    echo Characters WRONG
    exit 1
  fi
done
