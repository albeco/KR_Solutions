#include <stdio.h>
#define MAXSTRING 80

/* invert: invert n bits starting from position p from the right  */
int setbits(int x, int p, int n, int y);
int invert(int x, int p, int n);
int char2bin(char *sx);
void bin2char(int x, char *sx);

int main(void)
{
  char sx[MAXSTRING];
  char sz[MAXSTRING];
  int readEl = 0;
  int x, n, p;

  readEl += scanf("%s", sx);
  readEl += scanf("%d", &p);
  readEl += scanf("%d", &n);

  if (readEl != 3) {
    printf("#inputs: %d\n", readEl);
    return -1;
  }
  x = char2bin(sx);
  bin2char(invert(x, p, n), sz);
  printf("%s\n", sz);
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
