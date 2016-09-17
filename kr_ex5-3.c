#include <stdio.h>
#define MAXSTRING 80

void mystrcat(char s[], char t[]);
int main(void)
{
  char s[MAXSTRING], t[MAXSTRING];
  putchar('>');
  scanf("%s", s);
  putchar('>');
  scanf("%s", t);
  mystrcat(s, t);
  printf("%s\n", s);
  return 0;
}

void mystrcat(char s[], char t[])
{
  while (*s != '\0')
    s++;
  while ((*s++ = *t++) != '\0')
    ;
}
