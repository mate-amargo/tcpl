#include <stdio.h>

/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300 */

main()
{
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;     /* lower limit of temperature table */
  upper = 300;   /* upper limit */
  step = 20;     /* step size */

  fahr = lower;
  while (fahr <= upper) {
    celsius = (5.0/9.0) * (fahr-32.0);
    /*celsius = 5/9 * (fahr-32);*/
    /* If you do this, since 5 and 9 are both
       integeres, the division truncates the result to zero, therefore all
       temperatures would be zero
    */
    printf("%3.0f\t%6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }

}
