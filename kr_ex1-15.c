#include <stdio.h>

#define LOWER   0 // lower F temperature
#define UPPER   300 // uppuer F temperature
#define STEP    20  // increment F temperature

float fahr2cel(int temperature);

/* print Fahrenheit-Celsious table
   for fahr = -100, 20, ..., 300 */
int main()
{
  int fahr;

  printf("%6s %6s\n", "Fahr", "Cel");
  printf("-------------\n");
  for (fahr = LOWER; fahr <= UPPER; fahr += STEP) 
    printf("%6d %6.1f\n", fahr, fahr2cel(fahr));
}
  
// convert fahreneit degree to celsius
float fahr2cel(int x)
{
  return 5.0 / 9.0 * (x - 32.0);
}
