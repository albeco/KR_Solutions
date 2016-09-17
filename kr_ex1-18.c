#include <stdio.h>
#define MAXLINE 1000 // max length of text line

int mygetline(char line[], int maxlength);
void removeTrailSpace(char line[]);

/* remove trailing blakks and tabs at end of lines */
int main()
{
  int len; // current line length
  char line[MAXLINE]; // current line

  while ((len = mygetline(line, MAXLINE)) > 0)
    if (len > 1) {
      removeTrailSpace(line);
      printf("%s", line);
    }
}

/* getilne: read a line into s, return its length */
int mygetline(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if (c == '\n') { 
    s[i] = c; // since the for loop exit before putting the newline
    ++i;
  }
  s[i] = '\0'; // the end of string character
  return i;
}

/* removeTrailSpace: delete tabs and spaces from end of line */
void removeTrailSpace(char s[])
{
  int i = 0;
  int len;
  // finding length of line
  while (s[i] != '\0')
    ++i;
  len = i--;
  
  while ((i >= 0) && ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n')))
    --i;
  
  if (i < 0) {
    s[0] = '\0'; // delete the empty line
  }
  else {
    if (s[len - 1] == '\n')
      s[++i] = '\n';
    s[++i] = '\0';
  }
    
}
