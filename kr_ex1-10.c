#include <stdio.h>

/* copy input to output replacing tabs, backspaces and 
   newlines with escape characters                      */

int main()
{
  int c;

  while ((c = getchar()) != EOF)
    if (c == '\t') printf("\\t");
    else if (c == '\n') printf("\\n");
    else if (c == '\b') printf("\b");
    else putchar(c);

  return(0);
}
