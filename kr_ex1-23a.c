#include <stdio.h>

int readwritechar(void);
int readwritestring(void);
int skipcomment(void);

/* remove comments from c program */

/* this version can spot multiple errors in balancing chars and strings
    by reprocessing extra read chars. For example in a text which contains ' "
    the program reports both an unbalanced char and an unbalanced string */

int main() {
  int c;
  int extrachar = 0;
  
  c = getchar();
  while (c != EOF) {
    if (c == '\'') {
      c = readwritechar();
      if (c != '\'') {
	extrachar = 1;
	printf("\n-- unbalanced char --\n");
      }
    }
    else if (c == '\"') {
      c = readwritestring();
      if (c != '\"') {
	extrachar = 1;
	printf("\n-- unbalanced string --\n");
      }
    }
    else if (c == '/')
      if ((c = getchar()) == '*') {
	c = skipcomment();
	if (c != '/') {
	  extrachar = 1;
	  printf("\n-- unbalanced comment --\n");
	}
      }
      else {
	putchar('/');
	if (c != EOF)
	  extrachar = 1;
      }
    else
      putchar(c);
    /* skipping the char allows finding multiple errors */
    if (c != EOF && extrachar == 0)
      c = getchar();
    else
      extrachar = 0; /* reset the error to allow finding next one and avoid infinite loop */
  }
}

int readwritechar(void)
{
  int c;
  putchar('\'');
  if ((c = getchar()) == EOF || c  == '\'') /* EOF signals unbalanced char */ 
    ; 
  else if (c == '\\') { //escaped char
    putchar('\\');    
    if ((c = getchar()) != EOF) { 
      putchar(c);
      c = getchar();
    }
  }
  else { // single char
    putchar(c);
    c = getchar();
  }
  if (c == '\'') // does not print extra unbalanced char
    putchar(c);
  return c;
}

int readwritestring(void)
{
  int c;
  
  putchar('\"');
  c = getchar();
    while (c != '\"' && c != EOF) {
    if (c == '\\') {
      putchar('\\');
      c = getchar();
      if (c != EOF) {
	putchar(c); // no support of octal and hex escape char
	c = getchar();
      }
    }
    else {
      putchar(c);
      c = getchar();
    }
    }
    if (c == '\"') // does not print extra unbalanced char
      putchar(c);
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
