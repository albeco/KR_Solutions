#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

//int mygetline(char *line, int max);
int findpattern(FILE *fpi, char *filename, char *pattern, int number, int except);

/* find: print lines that match pattern from 1st arg  */
int main(int argc, char *argv[])
{
  FILE *fp;
  char *prog = argv[0];
  char pattern[MAXLINE];
  long lineno = 0;
  int c, except = 0, number = 0, found = 0;

  while (--argc > 0 && (*++argv)[0] == '-') {
    //printf("%d,%c\n",argc, (*argv)[0]);
    while ((c = *++argv[0]) != 0) {
      //printf("%c\n",c);
      switch (c) {
      case 'x':
	except = 1;
	break;
      case 'n':
	number = 1;
	break;
      default:
	fprintf(stderr, "%s: illegal option %c\n", prog, c);
	argc = 0;
	found = -1;
	return -1;
      }
    }
  }
  if (argc < 1) // the pattern to find is missing
    printf("Usage: find -x -n pattern file1 file2 ...\n");
  else {
    strcpy(pattern, *argv);
    if (argc > 1) // there is a file names list
      while (--argc) {
	if ((fp = fopen(*++argv, "r")) == NULL) {
	  fprintf(stderr, "cannot open file %s\n", *argv);
	  return 1;
	} else {
	  found += findpattern(fp, *argv, pattern, number, except);
	  fclose(fp);
	}
      }
    else // pattern match from standard input
      found += findpattern(stdin, "stdin", pattern, number, except);
  }
  return found;
}

int findpattern(FILE *fpi, char *filename, char *pattern, int number, int except)
#define MAXLINE 1000
{
  char line[MAXLINE];
  long lineno = 0;
  int found = 0;

  while (fgets(line, MAXLINE, fpi) != NULL) {
      lineno++;
      if ((strstr(line, pattern) != NULL) != except) {
	if (number)
	  printf("%s, %ld: ", filename, lineno);
	printf("%s", line);
	found++;
      }
    }
  return found;
}

/* find: print lines that match pattern from 1st arg - 1st version */
/* int main(int argc, char *argv[]) */
/* { */
/*   char line[MAXLINE]; */
/*   int found = 0; */

/*   if (argc != 2) */
/*     printf("Usage: find pattern\n"); */
/*   else */
/*     while (mygetline(line, MAXLINE) > 0) */
/*       if (strstr(line, argv[1]) != NULL) { */
/* 	  printf("%s", line); */
/* 	  found++; */
/* 	} */
/*   return found; */
/* } */

/* int mygetline(char *line, int max) */
/* { */
/*   int i, c; */

/*   for (i = 0; i < max-1 && (c=getchar()) != '\n' && c != EOF; i++) */
/*     *line++ = c; */
/*   if (c == '\n') { */
/*     i++; */
/*     *line++ = c; */
/*   } */
/*   *line = '\0'; */
/*   return i; */
/* } */

