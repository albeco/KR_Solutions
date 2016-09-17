#include <stdio.h>
#define MAXSTRING 100
#define NOTFOUND -1

int any(char *s1, char *s2);

int main(void)
{
  char s1[MAXSTRING];
  char s2[MAXSTRING];
  int firstpos;

  scanf("%s\n%s", s1, s2);
  firstpos = any(s1, s2);
  if (firstpos != NOTFOUND)
    printf("%d\n", firstpos);
  else
    printf("no matching characters\n");
  return firstpos;
}

int any(char *s1, char *s2)
{
  int i, k;

  for (i = 0; s1[i] != '\0'; i++) {
    for (k = 0; s2[k] != '\0' && s2[k] != s1[i]; k++)
      ;
    if (s2[k] != '\0')
      return i;
  }
  return NOTFOUND;
}
