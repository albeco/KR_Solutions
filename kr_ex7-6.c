#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000

// compare two files, print first differting lines
int main(int argc, char *argv[])
{
  FILE *fp1, *fp2;
  char s1[MAXLINE], s2[MAXLINE];
  
  if (argc != 3) {
    fprintf(stderr, "usage: %s file1 file2\n", argv[0]);
    exit(1);
  } 
  if ((fp1 = fopen(argv[1], "r")) == NULL ) {
       fprintf(stderr, "cannot open file %s\n", argv[1]);
       exit(2);
    }
  if ((fp2 = fopen(argv[2], "r")) == NULL ) {
       fprintf(stderr, "cannot open file %s\n", argv[2]);
       fclose(fp1);
       exit(2);
    }
  while (fgets(s1,MAXLINE, fp1) != NULL && fgets(s2, MAXLINE, fp2) != NULL)
    if (strcmp(s1, s2) != 0) {
      printf("%s%s", s1, s2);
      break;
    }
  fclose(fp1);
  fclose(fp2);
  exit(0);
}
