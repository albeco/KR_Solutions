#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define ALLOCSIZE 10000 /* size of available space */

char *lineptr[MAXLINES]; /* pointers to text lines  */

int readlines(char *lineptr[], int nlines, char buffer[], int bufsize);
void writelines(char *lineptr[], int nlines);

void myqsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(void)
{
  int nlines; /* number of input lines read */
  char allocbuf[ALLOCSIZE]; /* storage for alloc */

  if ((nlines = readlines(lineptr, MAXLINES, allocbuf, ALLOCSIZE)) >= 0) {
    myqsort(lineptr, 0, nlines-1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to be sorted\n");
    return 1;
  }
}

#define MAXLEN 1000 /* max length of any input line */
int mygetline(char *s, int n);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char allocbuf[], int bufsize)
{
  char *allocp = allocbuf; /* next free position */
  int len, nlines;
  char line[MAXLEN];

  nlines = 0;
  while ((len = mygetline(line, MAXLEN)) > 0)
    /* if (nlines >= maxlines || (p = alloc(len)) == NULL) */
    if (nlines >= maxlines || allocbuf + bufsize - allocp < len)
      return -1;
    else {
      line[len-1] = '\0'; /* delete newline */
      strcpy(allocp, line);
      lineptr[nlines++] = allocp;
      allocp += len;
    }
  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  int i;

  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

/* myqsort: sort v[left]...v[right] into increasing order */
void myqsort(char *v[], int left, int right)
{
  int i, last;
  void swap(char *v[], int i, int j);

  if (left >= right) /* do nothing if array contains */
    return;           /* fewer than two elements */
  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  myqsort(v, left, last-1);
  myqsort(v, last+1, right);
}
/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
  char *temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* mygetline: read a line into s, return length */
int mygetline(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if (c == '\n') 
    s[i++] = c;
  s[i] = '\0';
  return i;
}



