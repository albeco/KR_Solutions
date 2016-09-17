#include <stdio.h>
#define MAXLINE 80 // max length of text line
#define MAXBUFFER 1000 // max storage for long line

int mygetline(char line[], int maxlength);
void copy(char to[], char from[]);

/* print the longest input line */
int main()
{
  int len; // current line piece length
  int totlen; // current line total length
  int max; // maximum line length
  char line[MAXLINE]; // current line piece
  char buffer[MAXBUFFER]; // current line
  char longest[MAXBUFFER]; // longest line

  max = 0;
  totlen = 0;
    while ((len = mygetline(line, MAXLINE)) > 0) {
      if (totlen + len < MAXBUFFER) 
	copy(&(buffer[totlen]), line);
      
      // appending line to buffer
      totlen += len;

      // if buffer is bigger than current max, copy it     
      if (totlen > max) {
	max = totlen;
	copy(longest, buffer);
	//	printf("-%d- %s \n",len, line);
      }
      // a newline reset the buffer
      if (line[len-1] == '\n') {
	totlen = 0;
	buffer[0] = '\0';
      }
    }
  if (max > 0) // there was at least a line
    {
      printf("\n~~~\n");
      printf("total length: %d\n", max);
      printf("%s\n", longest);
    }
  return 0;
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

/* copy: copy 'from' into 'to'; assume 'to' is big enough */
void copy(char to[], char from[])
{
  int i;
  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}


