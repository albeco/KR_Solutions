#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 // max #lines to be sorted
#define MAXFIELDS 10 // max #of fields to be sorted for each line
#define FIELDSEP ' '

/* ext-17: support for ordering by fields with individual settings */
/* usage: myqsort -xyz -xyz - -xyz */
/* where x, y and z are one of the following options: -n for numeric
   order, -a for ascii order (also default), -f for ignoring the
   letter case, -d for ignoring non standard characters, -r for
   reversing the sort direction. For the not specified fields, default
   settings are used (ascii, ascending). For skipping a field just
   type'-' without any letters, as in the example above. */


// ex5-16: added flad -d for comparing only letters, numbers and blanks
// ex5-15: added flag -f for case insensitive sorting
// ex5-14: modified to handle -r flag (reverse order)

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void freelines(char *lineptr[], int nlines);

void myqsort(void *lineptr[], int left, int right,
             int (*comp[]) (const char *, const char *), int sortorder[], int nofields);
int numcmp(const char *, const char *);
int dircmp(const char *, const char *);
int skipfield(char const *, char const *) ;
int dircasecmp(const char *, const char *);
int fieldcomp(const char *, const char *, int (*sf[])(const char *, const char *), int sd[], int nofields);
int readNextField(char **line, char separator, char *nextfield);

// sort input lines
int main(int argc, char *argv[])
{
    int nlines; // #lines to be erad
    int numeric= 0; // 1 if numeric sort
    char *lineptr[MAXLINES]; // pointers to text lines
    int caseinsensitive = 0; // 0 for case insensitive
    int dirorder = 0;
    // here in the following item 0 is for default settings
    int sortorder[MAXFIELDS] ;
    int  (*sortfunc[MAXFIELDS]) (const char *, const char *);
    int i, j;
    char *s;
    
    for (i = 0; i < MAXFIELDS; i++) { // initialize with default settings
        sortorder[i] = 1;                        // ascending order and alphabetic order
        sortfunc[i] = &strcmp;
    }
    
    for (i  = 1, j = 0; i < argc && j  < MAXFIELDS; i++) {
        s = argv[i];
        if (*s == '-') {
	  if (s[1] == '\0') 
	    sortfunc[j] = &skipfield; //skipping the field
	  else {
            while (*++s != '\0') {
                if (*s == 'n')
                    numeric = 1;
                else if (*s == 'r')
                    sortorder[j] = -1;
                else if (*s == 'd')
                    dirorder = 1;
                else if (*s == 'f')
                    caseinsensitive = 1;
		else if (*s == 'a')
		  ; // default alphabetic comparison (use default setting)
		else {
		  printf("warning: unsupported command line option \'%s\' ", s);
		  printf("for field # %d\n", j+1);
		}
            }
            if (numeric)
                sortfunc[j] = &numcmp;
            else if (dirorder) {
                if (caseinsensitive)
                    sortfunc[j] =  &dircasecmp;
                else
                    sortfunc[j] = &dircmp;
            }
            else {
                if (caseinsensitive)
                    sortfunc[j] =  &strcasecmp;
                else
                    sortfunc[j] = &strcmp;
            }
	  }
            j++;
        }  else {
            printf("warning: unrecognized argument (%s)\n", argv[i]);
            continue;
        }
    }
    //nosetfields = j;
    
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        myqsort((void **) lineptr, 0, nlines-1, sortfunc, sortorder, MAXFIELDS);
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
void myqsort(void **v, int left, int right, int (*sortfunc[])(const char *, const char *),
             int sortorder[], int nofields)
{
    int i, last, cp;
    void swap(void **v, int a, int b);
    
    if (left >= right) // less than 2 elements
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        cp = fieldcomp(v[i], v[left], sortfunc, sortorder, nofields);
        if (cp < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    myqsort(v, left, last-1, sortfunc, sortorder, nofields);
    myqsort(v, last+1, right, sortfunc, sortorder, nofields);
}

#include <stdlib.h>
#include <ctype.h>

int skipfield(char const *s1, char const *s2)
{
  return 0;
}

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

//dir cmp: compares s1 and s2 only for letters, numbers and spaces
int isalphanum(char c);
char mytolower(char c);

int dircmp(const char *s1, const char *s2)
{
    for (; *s1 != '\0' && *s2 != '\0'; s1++, s2++) {
        while (!isalphanum(*s1) && *s1 != '\0')
            s1++;
        while (!isalphanum(*s2) && *s2 != '\0')
            s2++;
        if (*s1 != *s2)
            return (*s1 < *s2 ? -1 : 1);
    }
    return 0;
}

int dircasecmp(const char *s1, const char *s2)
{
    char c1, c2;
    
    for (; *s1 != '\0' && *s2 != '\0'; s1++, s2++) {
        while (!isalphanum(*s1) && *s1 != '\0')
            s1++;
        while (!isalphanum(*s2) && *s2 != '\0')
            s2++;
        
        if ((c1 = mytolower(*s1)) != (c2 =mytolower(*s2)))
            return (c1 < c2 ? -1 : 1);
    }
    return 0;
}

int isalphanum(char c)
{
    if (isdigit(c) || isspace(c) || isalpha(c))
        return c;
    else
        return 0;
}

char mytolower(char c)
{
    if (c >= 'A' && c <= 'Z')
        c += 'a'-'A';
    return c;
}


void swap(void **v, int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int fieldcomp(const char *line1, const char *line2,
              int (*sortfunc[])(const char *, const char *), int sortdir[], int nofields)
{
    int fieldno, cp = 0;
    char *np1;  char *np2;
    char s1[100]; char s2[100];
    
    for (fieldno = 0, np1 = (char *) line1, np2 = (char *) line2;
         *np1 != '\0' && *np2 != '\0' && fieldno < nofields; fieldno++) {
        readNextField(&np1, FIELDSEP, s1);
        readNextField(&np2, FIELDSEP,  s2);
        if ( (cp = (*sortfunc[fieldno])(s1, s2)) != 0)
            return cp * sortdir[fieldno];
    }
    return 0;
}

int readNextField(char **nextpos, char sep, char s[])
{
    char c;
    char *startpos = *nextpos;
    
    while (isspace(**nextpos))
        (*nextpos)++;
    while ((c = **nextpos) != '\0' && c != sep)
        *s++ = *(*nextpos)++;
    *s = '\0';
    
    if (**nextpos == sep)
        (*nextpos)++;
    
    return (int) (*nextpos - startpos);
}

#define MAXLINELENGTH 100
int mygetline(char s[], int lim);

int readlines(char *lineptr[], int nlines) {
    int i = 0, len = 0;
    char line[MAXLINELENGTH];
    char *p = NULL;
    
    while ((len = mygetline(line, MAXLINELENGTH)) > 0 && (p = malloc((len+1) * sizeof (char))) != NULL ) {
        if (line[len-1] == '\n')
            line[len-1] = '\0';
        strcpy(p, line);
        lineptr[i++] = p;
    }
    if (p == NULL)
        printf("readlines, warning: malloc error reading line no.%d\n", i);
    lineptr[i] = NULL;
    
    return i;
}


void writelines(char *lineptr[], int nlines){
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
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






