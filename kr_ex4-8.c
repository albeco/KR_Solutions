#include <stdio.h>
#define BUFSIZE 100
#define MAXLENGTH 20

/* getch and ungetch modified to support only one character of pushback */

int extrachar = '\0';
int getch(void);
void myungetch(int c);
int ungets(char s[]);
int getword(char s[], int maxlength);

int main()
{
  char c;
  c = getch();
  putchar(c);
  myungetch(c);
  c = getch();
  putchar(c);
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
  int c;
  if (extrachar == '\0')
    return getchar();
  else {
    c = extrachar;
    extrachar = '\0';
    return c;
  }
}

void myungetch(int c) // push char back on input
{
    if (extrachar != '\0')
        printf("myungetch: too many characters\n");
    else
      extrachar = c;
}

