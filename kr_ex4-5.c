#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXITER 10



/* adding commands to print ('?') top element of the stack
without popping it, duplicate it ('>'), swap two last elements ('<')
and clear the stack ('!') */

#define MAXOP 100 // max size of operands
#define NUMBER '0' // signal number has encountered
#define MATHFUN '\007'

int getop(char []);
void push(double);
double pop(void);
double applymathfun(char funname[], double x);



// reverse Polish calculator
int main()
{
  int type;
  double op2, op3;
  char s[MAXOP];
  int count = 0;
    
  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0)
	push(pop() / op2);
      else
	printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      if (op2 != 0)
	push((int) pop() % (int) op2);
      else
	printf("error: zero divisor\n");
      break;
    case '?':
      op2 = pop();
      printf("\t%.8g\n", op2);
      push(op2);
      break;
    case '>':
      op2 = pop();
      push(op2);
      push (op2);
      break;
    case '<':
      op2 = pop();
      op3 = pop();
      push(op2);
      push(op3);
      break;
    case '!':
      while (!isnan(op2 =pop()) && ++count <= MAXITER)
	;
      if (count == MAXITER) {
	printf("\n error: cannot clear stack, max iteration reached\n");
	return -1;
      }
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    case MATHFUN:
      op2 = pop();
      op3 = applymathfun(s, op2);
      if (isfinite(op3))
	push(op3);
      else
	printf("\tunsupported %s(%g)\n", s, op2);
      break;
    default:
      printf("error: unkwown command %s\n", s);
      break;
    }
  }
  return 0;
}

double applymathfun(char funname[], double x)
{
  if (strcmp(funname, "sin") == 0)
	     return sin(x);
  else if (strcmp(funname, "cos") == 0)
		  return cos(x);
  else if (strcmp(funname, "tan") == 0)
		  return tan(x);
  else if (strcmp(funname, "exp") == 0)
		  return exp(x);
  else if (strcmp(funname, "sqrt") == 0)
		  return sqrt(x);
  else if (strcmp(funname, "abs") == 0)
		  return abs(x);
  else if (strcmp(funname, "log") == 0)
		  return log(x);
  else if (strcmp(funname, "log10") == 0)
		  return log10(x);
  else // still unsupported mathematical function
    return NAN;
}

#define MAXVAL 100 // maximum depth of stack
int sp = 0; // next free stack position
double val [MAXVAL]; // value stack

//push: push f onto value stack
void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can\'t push %g\n", f);
}

// pop: pop and return top value from stack
double pop(void)
{
  if (sp >0)
    return val[--sp];
  else {
    printf("stack empty\n");
    return NAN;
  }
}

#include <ctype.h>
int getch(void);
void myungetch(int c);

// getop: get next operator or numeric operand
int getop(char s[])
{
  int i, c;
    
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ; // skipping white spaces
  s[1] = '\0';
  i = 0;
  if (c == EOF || c == '\n')
    return c; // reached end of line or file, stop here
  else          // otherwise read next character
    c  = getch();

  if ( isdigit(s[0]) || (s[0] == '.' && isdigit(c)) || //we have a number
      ((s[0] == '+' || s[0] == '-') && ( isdigit(c) || c == '.' )) )
    { // reading a number
    while (isdigit(c)) { // reading integer part
      s[++i] = c;
      c = getch();
    }
    if (c == '.') { //reading fraction part
      s[++i] = c;
      while (isdigit(c = getch()))
	s[++i] = c;
    }
    s[++i] = '\0';
    if (c != EOF)
      myungetch(c);
    if (i == 2 && s[1] == '.' && (s[0] == '+' || s[0] == '-'))
      {                            // one sign and a decimal separator are not a number
	myungetch(s[1]); // we put back the decimal separator
	return s[0];          // and return the sign to be reprocessed as operator
      }
    else
      return NUMBER;
  }
  else if (s[0] >= 'a' && s[0] <= 'z') { // reading a word
    while (c >= 'a' && c <= 'z') {        // made of alphabetic characters
      s[++i] = c;
      c = getch();
    }
    s[++i] = '\0';
    if (c != EOF)
      myungetch(c);
    return MATHFUN;
  }
  else { // single character operator
    if (c != EOF)
      myungetch(c);
    return s[0];
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
