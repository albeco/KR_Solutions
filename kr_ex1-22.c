#include <stdio.h>

#define MAXLENGTH 80
#define TABSIZE 8

/* fold: word wrap input text */

/* missing the check if an empty line contains more than MAXLENGTH chars
    also does not break long lines */


int main()
{
  int c = '\0';
  int colNo = 0;
  int nextcol = 0;
  char ss[MAXLENGTH+1];
  char ws[MAXLENGTH+1];
  int si = 0;
  int wi = 0;

  colNo = 0;
  c = getchar();
  while (c != EOF) {
    si = 0;
    while (c == ' ' || c == '\t') {
      ss[si++] = c;
      c = getchar();
    }
    ss[si] = '\0';
    if (c == '\n') {
      colNo = si = wi = 0;
      putchar('\n');
      c = getchar();
    }
    else if (c != EOF) {
      wi = 0;
      while (c != ' ' && c != '\t' && c != '\n' && c != EOF && wi < MAXLENGTH) {
	ws[wi++] = c;
	c = getchar();
      }
      ws[wi] = '\0';
      nextcol = colNo;
      for (si = 0; ss[si] != '\0'; si++)
	if (ss[si] == '\t')
	  nextcol +=  (TABSIZE - (nextcol % TABSIZE));
	else if (ss[si] == ' ')
	  ++nextcol;
	else
	  printf("\n--char instead of space--\n");
      nextcol += wi;
       if (nextcol <= MAXLENGTH) {
	printf("%s%s", ss, ws);
	colNo = nextcol;
      }
      else {
	printf("\n%s", ws);
	colNo = nextcol = wi;
      }
    }
  }
  return 0;
}
