#include <stdio.h>
#include <limits.h>

void itoa(int n, char s[]);

int main()
{
  int n = 0;
  char s[80];
    
  while (n != -1) {
    printf(">");
    scanf("%d",&n);
    itoa(n, s);
    printf(" %s\n", s);
  }
}

void itoa(int n, char s[]) {
  int sign;
  int i = 0;
  int j;
  char c;

  if ((sign = n) >= 0) {
    s[i++] = n % 10 + '0';
    n /= 10;
  }
  else {
    s[i++] = -(n % 10) + '0';
    n /= -10;
  }
  while (n > 0) {
    s[i++] = n % 10 + '0';
    n /= 10;
  }
  if (sign < 0)
    s[i++] = '-';
  s[i--] = '\0';
  /* reversing string */
  for (j = 0; j < i; j++, i--)
    c = s[j], s[j] = s[i], s[i] = c;
}
