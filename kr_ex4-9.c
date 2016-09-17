#include <stdio.h>
#define BUFSIZE 100
#define MAXLENGTH 20

/* updated myungetch() to fix the case of ungetched EOF */
/*   quick solution: EOF is not added to the buffer */

char buf[BUFSIZE]; // buffer for myungetch
int bufp = 0; // nextt free position in buf
int getch(void);
void myungetch(int c);
int ungets(char s[]);
int getword(char s[], int maxlength);

int main()
{
  int i;
  char s[80];
  /* while (getword(s, MAXLENGTH) != 0) */
  /*   printf("-%s-",s); */
  getword(s, MAXLENGTH);
  printf("-%s-",s);
  /* for (i=0;i<MAXLENGTH;i++) */
  /*   s[i] = '\0'; */
  ungets(s);
  i = getword(s, MAXLENGTH);
  printf("-%s(%d)-",s,i);
  return 0;
}

int getword(char s[], int maxlength)
{
  int i, c;
  while ((c = getch()) == ' ' || c == '\t' || c == '\n')
    ;
  for (i = 0; i < maxlength-1 && c != ' ' &&
	 c != '\t' && c!= '\n' && c != EOF; i++, c = getch())
    s[i] = c;
  s[i] = '\0';
  if (c != EOF)
    myungetch(c);
  return i;
  
}

int getch(void) // get a (possibly pushed back) char
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void myungetch(int c) // push char back on input
{
  if (c == EOF) {
    printf("error: cannot pushback EOF to input buffer\n");
    return;
  }
  if (bufp >= BUFSIZE)
        printf("myungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int ungets(char s[]) // put back string to input buffer
{
  int len = 0;
  while (s[len] != '\0')
    ++len;
  if (bufp+len < BUFSIZE) {
    while(len > 0)
      buf[bufp++] = s[--len];
    return 1;
    }
  else {
    printf("myungetch: too many characters\n");
    return 0;
  }
}
