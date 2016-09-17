#include <stdio.h>
#include <string.h>
#include <ctype.h>

// kr_ex5-18 making dcl recovering from input error

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int dcl(void);
int dirdcl(void);

int gettoken(void);
int tokentype; // type of last token
char token[MAXTOKEN]; // last token string
char name[MAXTOKEN]; // identifier name
char datatype[MAXTOKEN]; // data type = chr, int, etc.
char out[1000]; // output string

void cleanerrors(void);

void main(void) // convert declaration to words
{
     while (gettoken() != EOF) {         // 1st token on line
	  strcpy(datatype, token); // is the datatype
	  out[0] = '\0';
	  // parse rest of line
	  if (dcl() != 0 || tokentype != '\n') {
	    printf("syntax error\n");
	    /* printf("currently: tokentype = %s, name = %s, " */
	    /* 	   "datatype = %s, out = %s\n", token, name, datatype,
		   out); */
	    cleanerrors();
	     /* printf("currently: tokentype = %s, name = %s, " */
	     /* 	   "datatype = %s, out = %s\n", token, name,
			   datatype, out); */
	  }
	  else
	    printf("%s: %s %s\n", name, out, datatype);
     }
}

int gettoken(void) // return next token
{
     int c, mygetch(void);
     void unmygetch(int);
     
     char *p = token;

     while ((c = mygetch()) == ' ' || c == '\t')
	  ;
     if (c == '(') {
	  if ((c = mygetch()) == ')') {
	       strcpy(token, "()");
	       return tokentype = PARENS;
	  } else {
	       unmygetch(c);
	       return tokentype = '(';
	  }
     } else if (c == '[') {
	  for (*p++ = c; (*p++ = mygetch()) != ']'; )
	       ;
	  *p = '\0';
	  return tokentype = BRACKETS;
     } else if (isalpha(c)) {
	  for (*p++ = c; isalnum(c = mygetch()); )
	       *p++ = c;
	  *p = '\0';
	  unmygetch(c);
	  return tokentype = NAME;
     } else
	  return tokentype = c;
}


// dcl: parse a declarator
int dcl(void)
{
     int ns;

     for (ns = 0; gettoken() == '*'; ) // count *s
	  ns++;
     if (dirdcl() != 0)
       return -1;
     while (ns-- > 0)
	  strcat(out, " pointer to");
     return 0;
}

// dirdcl: parse a direct declarator
int dirdcl(void)
{
     int type;

     if (tokentype == '(' ) {
	  dcl();
	  if (tokentype != ')' ) {
	       printf("error: missing )\n");
	       //cleanerrors();
	       return -1;
	  }
     } else if (tokentype == NAME) //variable name
	  strcpy(name, token);
     else {
	  printf("error: expected name or (dcl)\n");
	  //cleanerrors();
	  return -1;
     }
     while ((type = gettoken()) == PARENS || type == BRACKETS)
       if (type == PARENS)
	 strcat(out, " function returning");
       else {
	 strcat(out, " array");
	 strcat(out, token);
	 strcat(out, " of");
       }
     return 0;
}

void cleanerrors(void)
{
  void cleangetch(void);
  token[0] = name[0] = datatype[0] = out[0] = '\0';
  cleangetch();
}

#define BUFSIZE 100
char buf[BUFSIZE]; // buffer for myunmygetch
int bufp = 0; // nextt free position in buf

int mygetch(void) // get a (possibly pushed back) char
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void unmygetch(int c) // push char back on input
{
  if (bufp >= BUFSIZE)
    printf("myunmygetch: too many characters\n");
  else
    buf[bufp++] = c;
}

void cleangetch(void)
{
  bufp = 0;
}

