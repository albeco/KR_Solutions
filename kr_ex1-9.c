#include <stdio.h>

/* copy input to output replacing multiple blanks with one */

int main()
{
  int newChar, lastChar;

  lastChar = -2;
  while ((newChar = getchar()) != EOF)
    {
      if ((newChar != ' ') || (lastChar != ' '))
	putchar(newChar);
      lastChar = newChar;
    }
  return(0);
}
