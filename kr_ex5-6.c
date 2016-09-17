#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#define MAXLINE 80

/* several functions using pointers instead of arrays */
int mygetline(char line[], int maxlength);
int atoi(char *s);
void itoa(int n, char *s);
void itoan(int n, char *s, int base);
void squeeze(char *s, int c); // delete c from s
void reverse (char *s);

int main(void)
{
    char ln[MAXLINE];
    char c;
    int i, b;
    scanf("%d", &i);
    itoa(i, ln);
    printf("%s\n", ln);
    
    return 0;
}

void reverse(char *s)
{
  char *t = s;
  char c;
  while (*t)
    ++t;
  --s;
  for (; s < t; ++s, --t) 
    c = *s, *s = *t, *t = c;
}

void squeeze(char *s, int c)
{
  char *t;
  for (t = s; *s != '\0'; ++s)
    if (*s != c)
      *t++ = *s;
  *t = '\0';
}

int atoi(char *s)
{
  int n = 0;
  int sign = (*s == '-') ? -1 : +1;

  if (*s == '+' || *s == '-')
    ++s;
  while (isdigit(*s))
    n = 10 * n + (*s++ -'0');
  return n * sign;
}

/* void itoa(int n, char *s) */
/* { */
/*   int sign; */
/*   char *t = s; */
/*   if (n < 0) { */
/*     n = -n; */
/*     sign = -1; */
/*   } */
/*   else */
/*     sign = 1; */
  
/*   do { */
/*     *s++ = n % 10 + '0'; */
/*   } while ((n /= 10)); */
/*   if (sign < 0) */
/*     *s++ = '-'; */
/*   *s = '\0'; */
/*   reverse(s); */
/* } */

void itoa(int n, char *s)
{ // version valid also for MIN_INT
  int sign;
  char *t = s;
  if (n < 0) {
    sign = -1;
    *s++ = -(n % 10) + '0';
    n /= -10;
  }
  else {
    sign = 1;
    *s++ = n % 10 + '0';
    n /= 10;
  }
  while (n) {
    *s++ = n % 10 + '0';
    n /= 10;
  };
  if (sign < 0)
    *s++ = '-';
  *s = '\0';
  reverse(t);
}

void itoan (int n, char *s, int base)
{
  int sign;
  char *t = s;
  if (base < 2 || base > 16) {
    printf("\nitoan: base(%d) must be between 2 and 16\n", base);
    return;
  }
  if (n < 0) {
    n = -n;
    sign = -1;
  }
  else
    sign = 1;
  
  do {
    *s++ = "0123456789ABCDEF"[n % base];
  } while ((n /= base));
  if (sign < 0)
    *s++ = '-';
  *s = '\0';
  reverse(t);
}


int mygetline(char line[], int maxlen)
  /* note for early EOF (try MAXLINE =8 and "123EOF" as input) it
     requires a second EOF to terminate, it is not clear why */
{  
    int i, c;
    for(i = 0;  i < maxlen-1 && (c = getchar()) != EOF && c != '\n'; i++)
        *line++ = c;
    if (c == '\n')
        ++i, *line++ = c;
    *line = '\0';
    return i;
}
