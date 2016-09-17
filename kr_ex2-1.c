#include <stdio.h>
#include <limits.h>

/* determine the size of char, short, int, long, both signed and unsigned */

int main()
{
  char c = 1;
  char c1 = 1;
  unsigned char uc = 1;
  short int s = 1;
  short int s1 = 1;
  unsigned short int us = 1;
  int i = 1;
  int i1 = 1;
  unsigned int ui = 1;
  long int li = 1;
  long int li1 = 1;
  unsigned long int ul = 1;
    
  while (li1 > 0) {
    c1 = c+1;
    if (c1 > c )
      c = 2*c+1;
    s1 = s+1;
    if (s1 > 0 )
      s = 2*s+1;
    i1 = i + 1;
    if (i1 > 0 )
      i = 2*i+1;
    li1 = li+1;
    if (li1 > 0)
      li = 2*li+1;
    //printf("%ld\n", li);
  }
    
  uc = 2*c + 1;
  us = 2*s + 1;
  ui = 2*i + 1;
  ul = 2*li + 1;

  printf("\ncalculated integer limits:");
  printf("\nmax char: %d, max unsigned char: %u", c, uc);
  printf("\nmax short: %d, max unsigned short %u", s, us);
  printf("\nmax int: %d, max unsigned int: %u ", i, ui);
  printf("\nmax long: %ld, max unsigned long: %lu", li, ul);
  printf("\nfrom limits.h:");
    printf("\nmax char: %d, max unsigned char: %u", CHAR_MAX, UCHAR_MAX);
  printf("\nmax short: %d, max unsigned short %u", SHRT_MAX, USHRT_MAX);
  printf("\nmax int: %d, max unsigned int: %u ", INT_MAX, UINT_MAX);
  printf("\nmax long: %ld, max unsigned long: %lu\n", LONG_MAX, ULONG_MAX);

  return 0;
}
