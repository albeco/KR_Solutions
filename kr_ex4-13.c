#include <stdio.h>
#define MAXSTRING 100

 /* reverse string using recursion */
int reverse(char s[], int i);

int main()
{
  char s[MAXSTRING];
  int narg = 1;
  int len;
  while (narg == 1) {
    putchar('>');
    narg = scanf("%s", s);
    if (narg == 1) {
      len = reverse(s, 0);
      printf(" %s(%d)\n", s, len);
    }
  }
}

int reverse(char s[], int i)
{
  int c;
  int pos = 0;
  
  if ((c = s[i]) != '\0') {
    pos = reverse(s, i+1);
    s[pos++] = c;
  }
  s[pos] = '\0';
  return pos;
}
