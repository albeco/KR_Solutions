#include <stdio.h>
#undef swap
#define swap(t, x, y) {t c; (c) = (x); (x) = (y); (y) = (c);}

int main()
{
  float a = 3.0;
  float b = 5.0;
  printf("%g, %g\n",a ,b);
  swap(float, a, b);
  //{int c; (c) = (a); (a) = (b); (b) = (c);};
  printf("%g, %g\n",a ,b);
}
