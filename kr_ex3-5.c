#include <stdio.h>
#include <limits.h>

void itob(int n, char s[], int b);

int main()
{
  int n = 0;
  int b = 10;
  char s[80];
    
  while (n != -1) {
    printf(">");
    scanf("%d,%d",&n, &b);
    itob(n, s, b);
    printf(" %s\n", s);
  }
  return 0;
}

void itob(int n, char s[], int b) {
  int sign;
  int i = 0;
  int j;
  int digit;
  char c;

  digit = (n % b);
  if ((sign = n) >= 0) {
    s[i++] = digit + (digit < 10 ? '0' : 'A'-10);
    n /= b;
  }
  else {
     s[i++] = -digit + (-digit < 10 ? '0' : 'A'-10);
    n /= -b;
  }
  while (n > 0) {
    digit = n % b;
    s[i++] = digit + (digit < 10 ? '0' : 'A'-10);
    n /= b;
  }
  if (sign < 0)
    s[i++] = '-';
  s[i--] = '\0';
  /* reversing string */
  for (j = 0; j < i; j++, i--)
    c = s[j], s[j] = s[i], s[i] = c;
}
