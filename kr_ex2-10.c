#include <stdio.h>

int main(void)
{
  int c = '\0';

  while ((c = getchar()) != EOF)
    putchar(c>='A' && c<='Z' ? c-'A'+'a' : c);
  return 0;
}
