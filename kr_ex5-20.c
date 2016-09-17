#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_SIZE 100
#define MAX_NO_TOKENS 100
#define MAX_LINE_SIZE 1000

// kr_ex5-20 expand dc to handle declaration with function argument
// types and qualifiers

enum { ENDDEC, NAME, PARENS, BRACKETS };

int istype(char *s); //  chack if string is a c type
int istypeprefix(char *s); // if keyword specifying following type
int isqualifier(char *s); // check if string is a c qualifier
int mygetline(char s[], int lim);
void dcl(void);
void dirdcl(void);
int gettoken(void);
int readtokenfromline(char *line, int maxtokens);
char tokenlist[MAX_NO_TOKENS][MAX_TOKEN_SIZE];
int typelist[MAX_NO_TOKENS];
int notokens; // number of tokens read
int itoken = 0; // current token number
char out[1000]; // output string
char name[MAX_TOKEN_SIZE]; // identifier name
char datatype[MAX_TOKEN_SIZE]; // data type = chr, int, etc.

// this version runs both dcl an undcl depending on the name by which
// it is called from the command line
int main(int argc, char *argv[])
{
  //int type;
  //char temp[MAX_TOKEN_SIZE];
  char line[MAX_LINE_SIZE];
  int i, type, linesize;
  char temp[MAX_TOKEN_SIZE];
	
  while ((linesize = mygetline(line, MAX_LINE_SIZE)) > 0) {
    for (itoken = 0; itoken < MAX_NO_TOKENS; itoken++) {
      *tokenlist[itoken] = '\0';
      typelist[itoken] = 0;
    }
    
    notokens = readtokenfromline(line, MAX_NO_TOKENS);
    itoken = 0;
        // undcl: convert word to declaration
    
    if (strstr(argv[0],"undcl") != 0) 
      { 
	strcpy(out, tokenlist[itoken]);
	while ((type = typelist[++itoken]) != '\n' && type != '\0')
	  if (type == PARENS || type == BRACKETS)
	    strcat(out, tokenlist[itoken]);
	  else if (type == '*') {
	    if (typelist[itoken+1] == '*' || typelist[itoken+1] == NAME)
	      sprintf(temp, "*%s", out);
	    else
	      sprintf(temp, "(*%s)", out);
	    strcpy(out, temp);
	  } else if (type == NAME) {
	    sprintf(temp, "%s %s", tokenlist[itoken], out);
	    strcpy(out, temp);
	  } else
	    printf("invalid input at %s\n", tokenlist[itoken]);
	printf("%s\n", out);
      }                            // dcl: convert declaration to word
    else if (strstr(argv[0], "dcl") != 0)  
      {
	strcpy(datatype, tokenlist[itoken++]); // first token is the datatype
	out[0] = '\0';
	dcl(); // parse rest of line
	/* if (tokentype != '\n') */
	/*   printf("syntax error\n"); */
	printf("%s: %s %s\n", name, out, datatype);
      }
    else {          // test mode
      for (i = 0; i < notokens; i++) {
        printf("token: %s, type: %d\n", tokenlist[i], typelist[i]);
      }
    }
  }
  return 0;
}

int readnexttoken(char **nextpos, char *token);

int readtokenfromline(char *line, int maxtokens)
{
  int tokno;
  int toktype;
  char token[MAX_TOKEN_SIZE];
  char *nextpos;

  tokno = 0;
  nextpos = (char *) line;
  while (tokno < maxtokens && *nextpos != '\0') {
    toktype = readnexttoken(&nextpos, token);
    if (toktype == '\0')
      break;
    else if (toktype == NAME && (istype(token) || isqualifier(token)) 
	     && tokno > 0 && typelist[tokno-1] == '(') {
      typelist[tokno-1] = PARENS; // it is a function argument list
      do {
	strcat(tokenlist[tokno-1], token);
	if (istypeprefix(token)) // add a space between qualifier and type
	    strcat(tokenlist[tokno-1], " ");
      } while (*nextpos != '\0' && (toktype = readnexttoken(&nextpos, token)) != ')');
      if (toktype == '\0')
	printf("error: \'%d\' instead of ) closing function arguments declaration\n", toktype);
      strcat(tokenlist[tokno-1], ")"); // add the ) even if misssing
    }
    else {
      strcpy(tokenlist[tokno], token);
      typelist[tokno++] = toktype;
    }
  }
  return tokno;
}

int readnexttoken(char **nextpos, char *p) // return next token
{
  // int c;
    
  //char *p = token;
    
  while (isspace(**nextpos))
    (*nextpos)++;
    
  if ((*nextpos)[0] == '(') {
    if ((*nextpos)[1] == ')') {
      strcpy(p, "()");
      *nextpos += 2;
      return PARENS;
    } else {
      p[0] = *(*nextpos)++;
      p[1] = '\0';
      return '(';
    }
  } else if ((*nextpos)[0] == '[') {
    for ( ; **nextpos != '\0' && **nextpos != ']'; (*nextpos)++)
      {
	*p++ = **nextpos;
      }
    if (**nextpos == ']') {
      *p++ = *(*nextpos)++;
    }
    *p = '\0';
    return BRACKETS;
  } else if (isalpha(**nextpos)) {
    for ( ; **nextpos != '\0' && isalnum(**nextpos); (*nextpos)++)
      *p++ = **nextpos;
    *p = '\0';
    return NAME;
  } else {
    p[0] = *(*nextpos)++;
    p[1] = '\0';
    return p[0];
  }
}


// dcl: parse a declarator
void dcl(void)
{
  int ns;
    
  for (ns = 0; typelist[itoken] == '*'; ns++) // count *s
    itoken++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}

// dirdcl: parse a direct declarator
void dirdcl(void)
{
  int type;
    
  if (typelist[itoken] == '(' ) {
    itoken++;
    dcl();
    if (typelist[itoken] != ')' )
      printf("error: missing )\n");
  } else if (typelist[itoken] == NAME) //variable name
    strcpy(name, tokenlist[itoken]);
  else
    printf("error: expected name or (dcl), received type:\'%d\'\n", typelist[itoken]);
  //  while ((type = gettoken()) == PARENS || type == BRACKETS)
  while ((type = typelist[++itoken]) == PARENS || type == BRACKETS)
    if (type == PARENS) {
      strcat(out, " function");
      strcat(out, tokenlist[itoken]);
      strcat(out, " returning");
    }
    else {
      strcat(out, " array");
      strcat(out, tokenlist[itoken]);
      strcat(out, " of");
    }
}



/* mygetline: read a line into s, return length
   this version skips the newline character */
int mygetline(char s[], int lim)
{
  int c = '\0', i = 0;
    
  for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  /* if (c == '\n') */
  /*     s[i++] = c; */
  s[i] = '\0';
  return i;
}

int istype(char *s)
{
  if (strcmp(s, "void") == 0   || strcmp(s, "char") == 0   ||
      strcmp(s, "short") == 0  || strcmp(s, "int") == 0    ||
      strcmp(s, "long") == 0   || strcmp(s, "float") == 0  ||
      strcmp(s, "double") == 0 || strcmp(s, "signed") == 0 ||
      strcmp(s, "unsigned") == 0)
    return 1;
  else
    return 0;
}

int istypeprefix(char *s)
{
  if (
      strcmp(s, "short") == 0  || strcmp(s, "long") == 0    ||
      strcmp(s, "signed") == 0 || strcmp(s, "unsigned") == 0 ||
      strcmp(s, "const") == 0  || strcmp(s, "volatile") == 0)
    return 1;
  else
    return 0;
}

int isqualifier(char *s)
{
  if (strcmp(s, "const") == 0 || strcmp(s, "volatile") == 0)
    return 1;
  else
    return 0;
}
