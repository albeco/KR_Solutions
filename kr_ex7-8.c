#include <stdio.h>
#include <stdlib.h>
#define MAXPAGESIZE 40

// printfile page by page with header and page number
int printfile(char *filename, int pagesize);

int main(int argc, char *argv[])
{
  int n;
  char *progname = argv[0];

  if (argc > 1)
    while (--argc > 0) {
      n = printfile(*++argv, MAXPAGESIZE);
      if (n != 0)
	fprintf(stderr, "%s: cannot open file %s\n", progname, *argv);
    }
  else
    printfile("stdin", MAXPAGESIZE);
  return 0;
}

#include <string.h>
#define MAXLINE 80
#define BOTTOMMARGIN 5
int printfile(char *filename, int pagesize)
{
  FILE *fp;
  char line[MAXLINE];
  int pageno = 1;
  int lineno;
  int i;
  if (strcmp(filename,"stdin") == 0) {
    fp = stdin;
  }
  else
    if ((fp = fopen(filename, "r")) == NULL) { // cannot open file
      return -1;
    }
  printf("%-*s  page %3d\n", MAXLINE-10, filename, pageno);
  for (i=1;i<=MAXLINE;i++)
    putchar('-');
  putchar('\n');
  lineno = 3;
  while (fgets(line, MAXLINE, fp) != NULL) {
    printf("%s", line);
    if (line[strlen(line)-1] != '\n')
      putchar('\n');
    if (lineno < pagesize - BOTTOMMARGIN)
      lineno++;
    else {
      for( ; lineno < pagesize; lineno++) // move to new page
	putchar('\n');
      printf("%-*s  page %3d\n", MAXLINE-10, filename, ++pageno);
      for (i=1;i<=MAXLINE;i++)
	putchar('-');
      putchar('\n');
      lineno = 3;
    }
  }
  for( ; lineno < pagesize; lineno++) // move to new page
    putchar('\n');
  return 0;
}
