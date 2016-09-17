#include <stdio.h>

int readwritechar(void);
int readwritestring(void);
int skipcomment(void);

/* remove comments from c program */
int main() {
  int c;

  c = getchar();
  while (c != EOF) {
    if (c == '\'') {
      c = readwritechar();
      if (c != '\'')
	printf("\n-- unbalanced char --\n");
    }
    else if (c == '\"') {
      c = readwritestring();
      if (c != '\"')
	printf("\n-- unbalanced string --\n");
    }
    else if (c == '/')
      if ((c = getchar()) == '*') {
	c = skipcomment();
	if (c != '/')
	  printf("\n-- unbalanced comment --\n");
      }
      else
	printf("/%c", c);
    else
      putchar(c);

    if (c != EOF)
      c = getchar();
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
  if (c != EOF)
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
    if (c != EOF)
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
