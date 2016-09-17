#include <stdio.h>
#define MAXPARENS 100 // max number unmatched parenthesis
#define UNMATCHEDRIGHTPAR 1
#define UNMATCHEDLEFTPAR 2
#define TOOMANYPARENS 3

int readchar(void);
int readstring(void);
int skipcomment(void);
int parensmatch(char a, char b);

/* check balanced (), [], and {} taking into account char constants,
    strings and comments */

int main() {
  int c = '\0';
  int extrachar = 0;
  int npar = 0;    /* index parenthesis list */
  char parensList[MAXPARENS];
  
  c = getchar();
  while (c != EOF) {
    if (c == '\'') {                                     /* reading const char */
      c = readchar();
      if (c != '\'') {
	extrachar = 1;                              
	printf("\n-- unbalanced char --\n");
      }
    }
    else if (c == '\"') {
      c = readstring();
      if (c != '\"') {                                    /*  reading a string */
	extrachar = 1;
	printf("\n-- unbalanced string --\n");
      }
    }
    else if (c == '/')
      if ((c = getchar()) == '*') {               /* skipping a comment */
	c = skipcomment();
	if (c != '/') {
	  extrachar = 1;
	  printf("\n-- unbalanced comment --\n");
	}
      }
      else {
	if (c != EOF)
	  extrachar = 1;
      }
    else if (c == '(' || c == '[' || c == '{') {
      if (npar < MAXPARENS)
	parensList[npar++] = c;
      else {
	printf("\n reached max number (%d) of unmatched parenthesis\n", MAXPARENS);
	return TOOMANYPARENS;
      }
      }
    else if (c == ')' || c == ']' || c == '}') {
      if (npar > 0 && parensmatch(parensList[npar-1], c) == 1) {
	parensList[npar-1] = '\0';
	--npar;
      }
      else {
	printf("\n unmatched parenthesis of type: \'%c\' \n", c);
	return UNMATCHEDRIGHTPAR;
      }
    }
      
    /* skipping the char allows finding multiple errors */
    if (c != EOF && extrachar == 0)
      c = getchar();
    else
      extrachar = 0; /* reset the error to allow finding next one and avoid infinite loop */
  }
  parensList[npar] = '\0';
  if (npar == 0)
    printf("\n all parenthesis are matched\n");
  else
    printf("\n unmatched parenthesis: \n%s\n", parensList);
}

int readchar(void)
{
  int c;
  if ((c = getchar()) == EOF || c  == '\'') /* EOF signals unbalanced char */ 
    ; 
  else if (c == '\\') { //escaped char
    if ((c = getchar()) != EOF) { 
      c = getchar();
    }
  }
  else { // single char
    c = getchar();
  }
  return c;
}

int readstring(void)
{
  int c;
  
  c = getchar();
    while (c != '\"' && c != EOF) {
    if (c == '\\') {
      c = getchar();
      if (c != EOF) {
	c = getchar();
      }
    }
    else {
      c = getchar();
    }
    }
  return c;
}

int skipcomment(void)
{
  int c;
  int insidecomment = 1;

  c = getchar();
  while (c != EOF && insidecomment == 1) {
    if (c == '*') {
      c = getchar();
      if (c == '/') {
	insidecomment = 0;
      }
      else if (c != EOF) {
	c = getchar();
      }
    }
    else {
      c = getchar();
    }
  }
  return c;
}

int parensmatch (char a, char b)
{
  if ((a == '(' && b == ')') ||
      (a == '[' && b == ']') ||
      (a == '{' && b == '}'))
    return 1;
  else
    return 0;
}
