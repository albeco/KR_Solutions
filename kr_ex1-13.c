#include <stdio.h>

#define MAX_WORD_LENGTH   20


/* counts digits, spaces and characters */

int main()
{
  int c, i;
  int n = 0;
  int nLongWords = 0;
  int wordIst[MAX_WORD_LENGTH + 1]; // element 0 of array unused for simplicity

  for (i = 0; i <= MAX_WORD_LENGTH; i++)
    wordIst[i] = 0;

  while ((c = getchar()) != EOF)
    if (c != ' ' && c != '\t' && c != '\n') {
      n = 1;
      while (((c = getchar()) != ' ') && (c != '\t') && (c != '\n') && (c != EOF))
	++n;
      if (n < MAX_WORD_LENGTH)
	++wordIst[n];
      else
	++nLongWords;
    }

  printf("\n word length histogram");
  printf("\n--------------------------\n");
  for (i = 1; i <= MAX_WORD_LENGTH; i++) {
    printf("%3d | %4d | ", i, wordIst[i]);
    for (n = 0; n < wordIst[i]; n++)
	putchar('#');
      putchar('\n');
  }
  printf("\nlong words = %d\n", nLongWords);
}
