#include <stdio.h>
#include <stdio.h>
#define MAXSTRING 80
#define TEST_ATOF(s) printf(s "\t%g\n",atof(s))
#define TEST_STRINDEX(s1,s2) printf("%s,%s\t%d\n", s1, s2, strindex(s1, s2))


char *mystrncpy(char *s, char *ct, int n);
/* Copy at most n characters of string ct to s; return s */
/* Pad with '\0' if t has fewer than n characters. */
char *mystrncat(char *s, char *st, int n);
/* Concatenate at most n characters of string ct to string s,
 terminates with '\0'; return s. */
int mystrncmp(char *cs, char *ct, int n);
/* compare at most n characters of string cs to string ct; return <0
 if cs<ct, 0 if cs==ct, or >0 if cs>ct */
double atof(char *s);
/* atof: convert string to double float number */
int strindex(char *s, char *t);
/* strindex: return index of t in s, -1 if none */
int getop(char *s);
/* getop: get next operator for RPN calculator */
void test_getop(void);
/* test_getop: test script for getop, ask user input parse it and display operators info */

int main(void)
{
    /* int i; */
    /* char s[MAXSTRING], t[MAXSTRING]; */
    /* int n = 5; */
    /* putchar('>'); */
    /* scanf("%s", s); */
    /* putchar('>'); */
    /* scanf("%s", t); */
    /* i = mystrncmp(s,t,n); */
    /* printf(" %d\n", i); */

/* /\* test atof *\/ */
  /* printf("test atof\n"); */
  /* TEST_ATOF("12.34"); */
  /* TEST_ATOF("-1.23"); */
  /* TEST_ATOF("0.23"); */
  /* TEST_ATOF("-0.23"); */
  /* TEST_ATOF(".23"); */
  /* TEST_ATOF("-.23"); */
  /* TEST_ATOF("1e10"); */
  /* TEST_ATOF("1.1e10"); */
  /* TEST_ATOF("0.1e10"); */
  /* TEST_ATOF(".1e10"); */
  /* TEST_ATOF("-.1e10"); */
  /* TEST_ATOF("1.2e-10"); */
  /* TEST_ATOF("-1.2e-10"); */

  /* /\* test strindex *\/ */
  /* printf("test strindex\n"); */
  /* TEST_STRINDEX("abc","abc"); */
  /* TEST_STRINDEX("abc","bc"); */
  /* TEST_STRINDEX("abc","c"); */
  /* TEST_STRINDEX("abc", ""); */
  /* TEST_STRINDEX("","abc"); */
  /* TEST_STRINDEX("", ""); */
  /* TEST_STRINDEX("a", "a"); */
  /* TEST_STRINDEX(" ", " "); */

  test_getop();
    
    return 0;
}

char *mystrncpy(char *s, char *ct, int n)
{
    char *olds = s;
    while (n-- > 0 && (*s++ = *ct++))
        ;
    while (n-- > 0)
        *s++ = '\0';
    return olds;
}

char *mystrncat(char *s, char *st, int n)
{
    char *olds = s;
    while (*s)
        s++;
    while (n > 0 && *st) {
        *s++ = *st++;
        --n;
    }
    *s = '\0';
    return olds;
}

int mystrncmp(char *cs, char *ct, int n)
{
    while (n > 0 && *cs == *ct) {
        if (*cs == '\0')
            return 0;
        --n, ++cs, ++ct;
    }
    if (n == 0)
        return 0;
    else
        return (*cs - *ct);
}

int strindex(char *s0, char *t0)
{
  char *s1, *s2;
  char *t;
  
  for (s1 = s0; *s1 != '\0'; s1++) {
    for (s2 = s1, t = t0; *t != '\0' && *s2 == *t; s2++, t++)
      ;
    if (t != t0 && *t == '\0')
      return s1-s0;
  }
  return -1;
}

#include <ctype.h>
double atof(char *s)
{
  double value, pow;
  char sign;
  int ep;

  while (*s == ' ' || *s == '\t')
    ++s;

  if (*s == '+' || *s == '-')
    sign = *s++;
  else
    sign = '+';
  
  for (value = 0; isdigit(*s); ++s)
    value = 10 * value + (double) (*s - '0');
  
  if (*s == '.') {
    ++s;
    for (pow = 1; isdigit(*s); ++s, pow *= 10)
      value = 10 * value + *s - '0';
    value /= pow;
  }
  
  if (*s == 'e' || *s == 'E') {
    ++s;
    pow = (*s == '-') ? 0.1 : 10;
    if (*s == '-' || *s == '+')
      ++s;
    for (ep = 0; isdigit(*s); ++s)
      ep = 10 * ep + *s - '0';
    while (ep-- > 0)
      value *= pow;
  }
  
  return (sign == '-' ? -value : value);
}

/* code for getop: from RPN calculator 
this version uses pointers instead of arrays*/

#define NUMBER '0' // signal number has encountered
#define MATHFUN '\007'
#define USERVARIABLE '\005'

void test_getop(void)
{
  int type;
  char s[100];
  while ((type = getop(s)) != EOF) {
    printf("type: ");
    switch(type) {
    case NUMBER:
      printf("NUMBER");
      break;
    case MATHFUN:
      printf("MATHFUN");
      break;
    case '+': case '*': case '-': case '/': case '%':
    case '?': case '>': case '<': case '!': case '^':
    case '.':
      putchar(type);
      putchar('\t');
      break;
    case '\n':
      printf("\\n");
      break;
    case USERVARIABLE:
      printf("USERVARIABLE");
      break;
    default:
      printf("char(%d)", type);
      break;
    }
    printf("\tstring: %s\n", s);
  }
}

#include <ctype.h>
int getch(void);
void myungetch(int c);

// getop: get next operator or numeric operand
int getop(char *s)
{
    int c;
    char *s0 = s;
    
    while ((*s = c = getch()) == ' ' || c == '\t')
        ; // skipping white spaces
    *(s+1) = '\0';
    //i = 0;
    if (*s == EOF || *s == '\n')
        return c; // reached end of line or file, stop here
    else          // otherwise read next character
        c  = getch();
    
    if ( isdigit(*s) || (*s == '.' && isdigit(c)) || //we have a number
        ((*s == '+' || *s == '-') && ( isdigit(c) || c == '.' )) )
    { // reading a number
        while (isdigit(c)) { // reading integer part
            *++s = c;
            c = getch();
        }
        if (c == '.') { //reading fraction part
            *++s = c;
            while (isdigit(c = getch()))
	      *++s = c;
        }
        *++s = '\0';
        if (c != EOF)
            myungetch(c);
        if ((s-s0) == 2 && *(s0+1) == '.' && (*s0 == '+' || *s0 == '-'))
        {                            // one sign and a decimal separator are not a number
	  myungetch(*(s0+1)); // we put back the decimal separator
            return *s0;          // and return the sign to be reprocessed as operator
        }
        else
	return NUMBER;
    }
    else if (*s == '#') {
      *(s+1) = '\0';
      if (c != EOF)
	myungetch(c);
      return USERVARIABLE;
    }
    else if (*s >= 'a' && *s <= 'z') { // reading a word
        while (c >= 'a' && c <= 'z') {        // made of alphabetic characters
	  *++s = c;
	  c = getch();
        }
        *++s = '\0';
        if (c != EOF)
	  myungetch(c);
        if (s - s0 == 1)
	  return USERVARIABLE;
        else
	  return MATHFUN;
    }
    else { // single character operator
      if (c != EOF)
	  myungetch(c);
        return *s;
    }
}

#define BUFSIZE 100
char buf[BUFSIZE]; // buffer for myungetch
int bufp = 0; // nextt free position in buf

int getch(void) // get a (possibly pushed back) char
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void myungetch(int c) // push char back on input
{
    if (bufp >= BUFSIZE)
        printf("myungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
