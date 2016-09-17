#include <stdio.h>
#define MAXSTRING 80

/* setbits(x,p,n,y) returns x with the n bits that begin at position p
   set to the rightmost n bits of y */
int setbits(int x, int p, int n, int y);
int char2bin(char *sx);
void bin2char(int x, char *sx);

int main(void)
{
  char sx[MAXSTRING];
  char sy[MAXSTRING];
  char sz[MAXSTRING];
  int readEl = 0;
  int x, y, n, p;

  readEl += scanf("%s", sx);
  readEl += scanf("%s", sy);
  readEl += scanf("%d", &p);
  readEl += scanf("%d", &n);

  if (readEl != 4) {
    printf("#inputs: %d\n", readEl);
    return -1;
  }
  x = char2bin(sx);
  y = char2bin(sy);
  printf("%d,%d\n",x,y);
  bin2char(setbits(x, p, n, y), sz);
  printf("%s\n", sz);
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

void bin2char(int x, char *sx)
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
