#include <stdio.h>

unsigned int char2bin(char *sx);
int bitcount(unsigned x);

int main()
{
  char sx[80];
  sx[0] = '\0';
  printf("enter binary number or \'q\' to exit\n");
  while (sx[0] != 'q') {
    putchar('>');
    scanf("%s", sx);
    if (sx[0] != 'q')
      printf("bitcount = %d\n", bitcount(char2bin(sx)));
  }
  return 0;
}

unsigned int char2bin(char *sx)
{
  unsigned int i;
  unsigned int n = 0;
  for (i = 0; sx[i] != '\0'; ++i)
    n = 2*n + sx[i]-'0';
  return n;
}

int bitcount(unsigned x)
{
  int b = 0;
  while (x != 0) {
    x &= (x-1);
    ++b;
  }
  return b;
}
