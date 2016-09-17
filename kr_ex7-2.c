#include <stdio.h>
#include <ctype.h>
#define MAXCOL 80
#define TABSIZE 8

int main(void)
{
  int c;
  int colno = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      putchar(c);
      colno += TABSIZE - (colno % TABSIZE);
    } else if (c == '\n') {
      putchar(c);
      colno = 0;
    } else if (isprint(c)) {
      putchar(c);
      colno++;
    } else { // display non printable chars as \hex
      printf("\\%2x", c);
      colno += 3;
    }
    if (colno >= MAXCOL) {
      putchar('\n');
      colno = 0;
    }
  }
  return 0;
}
