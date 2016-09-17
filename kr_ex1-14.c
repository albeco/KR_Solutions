#include <stdio.h>

#define ASCIISIZE 256

/* print histogram of frequency of input characters */
int main()
{
  int c;
  int freq[ASCIISIZE];

  for (c = 0; c <= ASCIISIZE; c++)
    freq[c] = 0;

  while ((c = getchar()) != EOF)
    if (c <= ASCIISIZE)
      ++freq[c];

  putchar('\n');
  for (c = 0; c < ASCIISIZE; c++) {
    if (freq[c] > 0) {
      if (c == '\t')
	printf("\\t");
      else if (c == '\n')
	printf("\\n");
      else
	printf(" %c", c);
      
      printf(" | %4d | ", freq[c]);
      for ( ; freq[c] > 0; --freq[c])
	putchar('*');
      putchar('\n');
    }
  }
}
