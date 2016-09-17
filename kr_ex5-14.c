#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 // max #lines to be sorted

// modified to handle -r flag (reverse order)

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void freelines(char *lineptr[], int nlines);

void myqsort(void *lineptr[], int left, int right,
             int (*comp) (void *, void *), int sortorder);
int numcmp(const char *, const char *);

// sort input lines
int main(int argc, char *argv[])
{
  int nlines; // #lines to be erad
  int numeric = 0; // 1 if numeric sort
  char *lineptr[MAXLINES]; // pointers to text lines
  int sortorder = 1; // -1 reverse order
  int i;
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-n") == 0)
      numeric = 1;
    else if (strcmp(argv[i], "-r") == 0)
      sortorder = -1;
  }
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    myqsort((void **) lineptr, 0, nlines-1,
	    (int (*)(void *, void *)) (numeric ? numcmp : strcmp), sortorder);
    writelines(lineptr, nlines);
    freelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to be sort\n");
    freelines(lineptr, nlines);
    return 1;
  }
}

// myqsort: sort v[left]...v[right] with increasing order
void myqsort(void **v, int left, int right, int (*comp)(void *, void *),
	     int sortorder)
{
  int i, last;
    void swap(void **v, int a, int b);
    
    if (left >= right) // less than 2 elements
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) * sortorder < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    myqsort(v, left, last-1, comp, sortorder);
    myqsort(v, last+1, right, comp, sortorder);
}

#include <stdlib.h>
// numcmp: compares s1 and s2 numerically
int numcmp(const char *s1, const char *s2)
{
    double v1, v2;
    
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void **v, int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define MAXLINELENGTH 100
int mygetline(char s[], int lim);

int readlines(char *lineptr[], int nlines) {
    int i = 0, len = 0;
    char line[MAXLINELENGTH];
    char *p = NULL;
    
    while ((len = mygetline(line, MAXLINELENGTH)) > 0 && (p = malloc((len+1) * sizeof (char))) != NULL ) {
        strcpy(p, line);
        lineptr[i++] = p;
    }
    if (p == NULL)
        printf("readlines, warning: mallor error reading line no.%d\n", i);
    lineptr[i] = NULL;
    
    return i;
}


void writelines(char *lineptr[], int nlines){
  int i;
    for (i = 0; i < nlines; i++)
        printf("%s", lineptr[i]);
    return;
}

void freelines(char *lineptr[], int nlines) {
    int i = 0;
    for (i = 0; i < nlines; i++) {
        if (lineptr[i] != NULL) {
            free(lineptr[i]);
            lineptr[i] = NULL;
        }
    }
    return;
}

/* mygetline: read a line into s, return length */
int mygetline(char s[], int lim)
{
    int c = '\0', i = 0;
    
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') 
        s[i++] = c;
    s[i] = '\0';
    return i;
}






