#include <stdio.h>

int main()
{
  int c;
  int nBlanks = 0;
  int nTabs = 0;
  int nLines = 0;

  while ((c = getchar()) != EOF)
    if (c == ' ')
      nBlanks++;
    else if (c == '\t')
      nTabs++;
    else if (c == '\n')
      nLines++;
  printf("\n--------------\n");
    printf("\nnBlanks = %4d, nTabs = %4d, nLines = %4d\n", nBlanks, nTabs, nLines);
  return(0);
}
