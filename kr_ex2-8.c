#include <stdio.h>
#define MAXSTRING 80

/* rightrot: return bit pattern rotatad n position to right  */
int setbits(int x, int p, int n, int y);
int invert(int x, int p, int n);
unsigned int rightrot(unsigned int x, int n);
int char2bin(char *sx);
void bin2char(unsigned int x, char *sx);

int main(void)
{
  char sx[MAXSTRING];
  char c[MAXSTRING];
  int readEl = 0;
  int x, y, n, p;

  readEl += scanf("%s", sx);
  readEl += scanf("%d", &n);

  if (readEl != 2) {
    printf("#inputs: %d\n", readEl);
    return -1;
  }
  
  x = char2bin(sx);
  y = rightrot(x, n);
  bin2char(y,c), printf("]%s\n", c);
  /* bin2char(y, sz); */
  /* printf("%s\n", sx); */
}

unsigned int rightrot(unsigned int x, int n)
{
  unsigned int y;
  unsigned int mask;
  char c[80];
  /* mask = ~0; */
  for (y = x, mask = (~0 << n); mask != 0; mask <<= 1)
    y <<= 1;
  
  return (y | (x >> n));
}

int invert(int x, int p, int n)
{
  int mask = (~(~0 << n)) << (p-n+1);
  return (~x & mask) | (x & ~mask);
}

int setbits(int x, int p, int n, int y)
{
  /* printf("\n-%d,%d,%d-\n", p,n,p-n+1); */
  int mask = (~(~0 << n)) << (p-n+1);
  y = (y << p-n+1) & mask;
  return 
    (x & ~mask) | y;
}

int char2bin(char *sx)
{
  int i;
  int n;
  for (i = n = 0; sx[i] != '\0'; ++i)
    n = 2*n + sx[i]-'0';
  return n;
}

void bin2char(unsigned int x, char *sx)
{
  int c = '\0';
  int i = 0;
  int j = 0;
  if (x == 0)
    sx[i++] = '0';

  while (x != 0) {
    sx[i++] = (x & 01) + '0';
    x >>= 1;
  }
  sx[i--] = '\0';
  for (j = 0; j < i; j++, i--)
    c = sx[j], sx[j] = sx[i], sx[i] = c;
  return ;
}
