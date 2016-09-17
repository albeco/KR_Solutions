#include <stdio.h>
#define MAXSTRING 100

void squeeze(char *s1, char *s2);

int main(void)
{
  char s1[MAXSTRING];
  char s2[MAXSTRING];

  scanf("%s\n%s", s1, s2);
  squeeze(s1, s2);
  printf("%s\n", s1);
  return 0;
}

void squeeze(char *s1, char *s2)
{
  int i, j, k;

  for (i = j = 0; s1[i] != '\0'; ++i) {
    for (k = 0; s2[k] != '\0' && s2[k] != s1[i]; ++k)
      ;
    if (s2[k] == '\0')
      s1[j++] = s1[i];
  }
  s1[j] = '\0';
}
