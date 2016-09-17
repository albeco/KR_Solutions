#include <stdio.h>
#define MAXSTRING 80

/* strend(s, t): return 1 if string t occurs at the end of string s, 0 otherwise */
int strend(char s[], char t[]);

int main(void)
{
  char s[MAXSTRING], t[MAXSTRING];
  int found = 0;
  
  putchar('>');
  scanf("%s", s);
  putchar('>');
  scanf("%s", t);
  found = strend(s, t);
  printf("%s\n", found ? "yes" : "no");
  return 0;
}

char *mystrncpy(char *s, char *ct, int n)
{
  while (n-- > 0 && (*s++ = *t++))
    ;
}
