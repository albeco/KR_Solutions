#include <stdio.h>
#include <ctype.h>
#define ARRSIZE 10
#ifdef ungetch
#undef ungetch
#endif

int getch(void);
void ungetch(int c);
int getint(int *pn);

int main(void)
{
  int n, x[ARRSIZE];
  for (n = 0; n < ARRSIZE && getint(&x[n]) != EOF; n++)
    printf("%d\t", x[n]);
  putchar('\n');
  return 0;
}

int getint(int *pn)
{
  int c, sign;

  while (isspace(c = getch()))
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0; // not a number
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    c = getch();
    if (!isdigit(c)) {
      ungetch(c);
      return 0;
    }
  }
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

#define BUFSIZE 100
char buf[BUFSIZE]; // buffer for myungetch
int bufp = 0; // nextt free position in buf

int getch(void) // get a (possibly pushed back) char
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push char back on input
{
    if (bufp >= BUFSIZE)
        printf("myungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
