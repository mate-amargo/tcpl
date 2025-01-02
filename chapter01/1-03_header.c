/*
 * Exercise 1-3. Modify the temperature conversion program to print a heading
 * above the table. □
 */

#include <stdio.h>

main()
{
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;     /* lower limit of temperature table */
  upper = 300;   /* upper limit */
  step = 20;     /* step size */

  fahr = lower;
  printf("Fahrenheit\tCelsius\n");
  while (fahr <= upper) {
    celsius = (5.0/9.0) * (fahr-32.0);
    printf("%6.0f\t\t%6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }

}
