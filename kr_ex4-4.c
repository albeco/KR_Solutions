#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXITER 10


/* adding commands to print ('?') top element of the stack
without popping it, duplicate it ('>'), swap two last elements ('<')
and clear the stack ('!') */

#define MAXOP 100 // max size of operands
#define NUMBER '0' // signal number has encountered

int getop(char []);
void push(double);
double pop(void);



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
    default:
      printf("error: unkwown command %s\n", s);
      break;
    }
  }
  return 0;
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
    ;
  s[1] = '\0';
  i = 0;
  if (c == '+' || c == '-') {
    c = getch();
    if (!isdigit(c) && c != '.') {
      myungetch(c);
      return s[0];
    }
    else
      s[++i] = c;
  }
  else if (!isdigit(c) && c != '.') {
    return c;
  }// not a number
  if (isdigit(c)) //collect integer part
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.') // collect fraction part
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    myungetch(c);
  return NUMBER;
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
