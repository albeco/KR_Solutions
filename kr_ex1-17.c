#include <stdio.h>
#define MAXLINE 1000 // max length of text line
#define NO_COLUMN 80 // columns in a page

int mygetline(char line[], int maxlength);

/* print all input lines longer than 80 characters */
int main()
{
  int len; // current line length
  char line[MAXLINE]; // current line

  while ((len = mygetline(line, MAXLINE)) > 0)
    if (len > NO_COLUMN)
      printf("%s", line);

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

