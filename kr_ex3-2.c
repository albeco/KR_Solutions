#include <stdio.h>
#include <string.h>

/* convert escapes character while copying a string */
void escape(char to[], char from[]);
int mygetline(char line[], int maxlength);

int main(void){
  char s[80], t[80];
  
  while (mygetline(t, 80) > 0) {
  escape(s, t);
  printf("%s\n", s);
  }
  return 0;
}

void escape(char s[], char t[])
{
  int i, j;
  for (i = j = 0; t[i] != '\0'; i++)
    switch(t[i]) {
    case '\t':
      s[j++] = '\\';
      s[j++] = 't';
      break;
    case '\n':
      s[j++] = '\\';
      s[j++] = 'n';
      break;
    case '\\':
      s[j++] = '\\';
      s[j++] = '\\';
      break;
    case '\'':
      s[j++] = '\\';
      s[j++] = '\'';
      break;
    case '\"':
      s[j++] = '\\';
      s[j++] = '\"';
      break;
    case '\?':
      s[j++] = '\\';
      s[j++] = '\?';
      break;
    default:
      s[j++] = t[i];
      break;
    }
  s[j] = '\0';
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

