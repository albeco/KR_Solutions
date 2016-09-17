#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000 // max input line length
#define MAXTAILSIZE 100
#define DEFAULTTAIL 10

int mygetline(char line[], int maxline);

static int tailsize = DEFAULTTAIL;
static int tailpos = 0;
static char *taillines[MAXTAILSIZE];

int storetail(char *newline, int newlinesize);
void readtail(void);
void freetail(void); // release the memory associated with the tail

int main(int argc, char *argv[])
{
    int len;
    char line[MAXLINE];

    for (int i = 0; i < MAXTAILSIZE; i++) // initialize tail lines
      taillines[i] = NULL;

    if (argc>1 && *argv[1] == '-') {
      tailsize = atoi(argv[1]+1);
      if (tailsize > MAXTAILSIZE) {
	tailsize = MAXTAILSIZE;
	printf("warning: max tail size: %d\n", MAXTAILSIZE);
      }
    }
    //printf("tail size: %d\n", tailsize);
    while ((len = mygetline(line, MAXLINE)) > 0) {
      storetail(line, len);
    }
    readtail();
    freetail();
}

void readtail(void)
{
  for(int i = 0; i < tailsize; i++) {
    printf("%s", taillines[tailpos] == NULL ? "" : taillines[tailpos]);
    tailpos = (tailpos+1) % tailsize;
  }
}

int storetail(char *newline, int newlinesize)
{
  taillines[tailpos] = // allocates space for n chars + 1 end-of-line '\0'
    realloc(taillines[tailpos], (newlinesize+1) * sizeof (char));
  strcpy(taillines[tailpos], newline);
  tailpos = (tailpos+1) % tailsize;
  return tailpos;
}

void freetail(void)
{
  for (int i = 0; i < tailsize; i++) {
    free(taillines[i]);
    taillines[i] = NULL;
  }
}

int mygetline(char s[], int lim)
{
    int c = EOF, i = 0;
    
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c =='\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
