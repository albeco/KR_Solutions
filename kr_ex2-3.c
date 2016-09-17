#include <stdio.h>
#include <string.h>
#define MAXDIGITS 100
#define NONVALIDHEXSTRING 1
#define NONVALIDCHAR 2

/* htoi: convert a string of hexadecimal digits to an integer value */

int main(void)
{
  char hstring[MAXDIGITS+1];
  int i;
  int hexnum;
  int nextdigit;
  
  for (i = 0; i <= MAXDIGITS; i++)
    hstring[i] = '\0';

  scanf("%s", hstring);
  if (strlen(hstring) < 3 || hstring[0] != '0' ||
      (hstring[1] != 'x' && hstring[1] != 'X')) {
    printf("\n A hex number must contain at least \'0x\' and a digit.\n");
    return NONVALIDHEXSTRING;
  }

  hexnum = 0;
  for (i = 2; i < MAXDIGITS && hstring[i] != '\0'; ++i) {
    if (hstring[i] >= '0' && hstring[i] <= '9')
      nextdigit = hstring[i] - '0';
    else if (hstring[i] >= 'a' && hstring[i] <= 'f')
      nextdigit = hstring[i] - 'a' + 10;
    else if (hstring[i] >= 'A' && hstring[i] <= 'F')
      nextdigit = hstring[i] - 'A' + 10;
    else {
      printf("\nnon valid hex character: \'%c\'\n", hstring[i]);
      return NONVALIDCHAR;
    }
    hexnum = 16 * hexnum + nextdigit;
  }
  printf("\ndecimal rapresentation: %d\n", hexnum);
  return 0; 
}
