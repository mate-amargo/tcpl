#include <stdio.h>

float fahr_to_celsius(float fahr);

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
    printf("%6.0f\t\t%6.1f\n", fahr, fahr_to_celsius(fahr));
    fahr = fahr + step;
  }

}

float fahr_to_celsius(float fahr)
{
  return (5.0/9.0) * (fahr-32.0);
}
