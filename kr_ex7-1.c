#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int c;
  int (*changecase)(int);
  
  if (strstr(argv[0], "tolower") != NULL)
    changecase = &tolower;
  else if (strstr(argv[0], "toupper") != NULL)
    changecase = &toupper;
  else {
    printf("error: command name should be \'tolower\' or \'toupper\'.\n");
    return -1;
  }
  
  while ((c = getchar()) != EOF)
    putchar(changecase(c));

  return 0;
}
