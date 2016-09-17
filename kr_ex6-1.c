#include <stdio.h>
#include <ctype.h>
#include <string.h>

// kr_ex6-1 handles undescores, string constants, comments and
// preprocessor control lines

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

struct key {
  char *word;
  int count;
} keytab[] = {
  "auto",       0,
    "break",    0,
    "case",     0,
    "char",     0,
    "const",    0,
    "continue", 0,
    "default",  0,
    "unsigned", 0,
    "void",     0,
    "volatile", 0,
    "while",    0
    };


int getword(char *, int);
int mybinsearch(char *, struct key *, int);


// count C keywords
int main()
{
  int n;
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0]))
      if ((n = mybinsearch(word, keytab, NKEYS)) >= 0)
	keytab[n].count++;
  }
  for (n = 0; n < NKEYS; n++)
    if (keytab[n].count > 0)
      printf("%4d %s\n", keytab[n].count, keytab[n].word);
  return 0;
      
}

// mybinsearch: find word in tab[0]...tab[n-1]
int mybinsearch(char *word, struct key tab[], int n)
{
  int cond, low, high, mid;

  low = 0;
  high = n-1;
  while (low <= high) {
    mid = (low+high) / 2;
    if ((cond = strcmp(word, tab[mid].word)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

// getword: get next word or character from input
int getword(char *word, int lim)
{
  int c, mygetch(void);
  void myungetch(int);
  int insidecomment = 0;

  char *w = word;

  while (isspace(c = mygetch()))
    ; //skipping spaces
  
  if (c == '#') {
    if (!isalpha(c=mygetch())) { 
      myungetch(c);
      strcpy(word, "#");
      return '#';
    }
    else { //skipping preprocessor lines
      while (c != EOF && c != '\n')
	c = mygetch();
      if (c != EOF)
	while (isspace(c = mygetch()))
	  ; //skipping spaces
    }
  } else if (c == '/') {
    if ((c = mygetch()) != '*') { 
      myungetch(c);
      strcpy(word, "/");
      return '/';
    } else { // skipping a comment
      insidecomment = 1;
      while (insidecomment && (c = mygetch()) != EOF) {
	if (c == '*' && ((c = mygetch()) == EOF || c == '/'))
	  insidecomment = 0;
      }
      if (c != EOF)
	while (isspace(c = mygetch()))
	  ; //skipping spaces
    }
  }

  if (c != EOF)
    *w++ = c;

  if (c == '\"') { // string litteral
    while ((c = mygetch()) != '\"' && c != EOF)
      *w++ = c;
    *w++ = '\"';
    *w = '\0';
    if (c == EOF)
      myungetch(c); // note that standard ungetch does not allow EOF pushback
    return word[0];
  } else if (!isalpha(c) && c != '_') {
    *w = '\0';
    return c;
  }
  for ( ; --lim > 0; w++) {
    //printf("-%d-\n",lim);
    if (!isalnum(*w = mygetch()) && *w != '_') {
      myungetch(*w);
      break;
    }
  }
  *w = '\0';
  return word[0];
}

#define BUFSIZE 100
char buf[BUFSIZE]; // buffer for myunmygetch
int bufp = 0; // nextt free position in buf

int mygetch(void) // get a (possibly pushed back) char
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void myungetch(int c) // push char back on input
{
  if (bufp >= BUFSIZE)
    printf("myunmygetch: too many characters\n");
  else
    buf[bufp++] = c;
}
