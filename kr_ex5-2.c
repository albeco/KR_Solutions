#include <stdio.h>
#include <ctype.h>
#define ARRSIZE 10
#ifdef myungetch
#undef myungetch
#endif

int getch(void);
void myungetch(int c);
int getint(int *pn);
int getfloat(float *pn);

int main(void)
{
    int n;
    float x[ARRSIZE];
    for (n =0; n < ARRSIZE; n++)
        x[n] = 0;
    for (n = 0; n < ARRSIZE && getfloat(&x[n]) != EOF; n++)
        printf("%g\t", x[n]);
    putchar('\n');
    return 0;
}

int getint(int *pn)
{
    int c, sign;
    
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        myungetch(c);
        return 0; // not a number
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            myungetch(c);
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        myungetch(c);
    return c;
}

int getfloat(float *pn)
{
    int c, sign;
    float pow;
    while (isspace(c = getch()))
        ;
    if (c == EOF)
        return c;
    if (!isdigit(c) && c != '+' && c != '-' && c != '.') {
        myungetch(c);
        return 0;
    }
    sign = (c == '-' ? -1 : 1);
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c) && c != '.') {
            myungetch(c);
            return 0;
        }
    }
    *pn = 0;
    while (isdigit(c)) {
        *pn = 10 * *pn + (c - '0');
        c = getch();
    }
    if (c == '.') {
        for (pow = 1; isdigit(c = getch()); pow *= 10)
            *pn = 10 * *pn + (c - '0');
        *pn /= pow;
    }
    if (c =='e' || c == 'E') {
      int epw = 0;
      float mult;
      c = getch();
      mult = (c == '-') ? 0.1 : 10;
      if (c == '-' || c == '+')
	c = getch();
      for (epw = 0; isdigit(c); c = getch())
	epw = 10 * epw + (c - '0');
      while (epw-- > 0)
	*pn *= mult;
    }
    *pn *= (float) sign;
    if (c != EOF)
        myungetch(c);
    return c;
}

#define BUFSIZE 100
char buf[BUFSIZE]; // buffer for mymyungetch
int bufp = 0; // nextt free position in buf

int getch(void) // get a (possibly pushed back) char
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void myungetch(int c) // push char back on input
{
    if (bufp >= BUFSIZE)
        printf("mymyungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
