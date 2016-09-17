#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000 // max input line length
#define NTAB 8
#define MAXTABNO 100 // maximum length of tabs list
#define ENDOFTABS 0

/* This version accept list of tabs from command line. The number zero
 is used as list terminator and it is automatically added. When the
 list ends the standard tab sequence is applied.  Note that the
 program works both as detab and as entab, depending on the name by
 which it is called from the command line.*/

// detab: replaces tabs with spaces, assuming a tab every N columns
// entab: replaces blanks with tabs and min no. of blanks

int mygetline(char line[], int maxline);
void mydetab(char detabbed[], char tabbed[], int *tablist, int ntab);
void myentab(char entabbed[], char line[], int *tablist, int ntab);
int *findnexttab(int n, int *tablist, int defaulttab, int *nexttabpos);

// reverse input one line at time
int main(int argc, char *argv[])
{
    int len;
    char line[MAXLINE];
    char etline[MAXLINE];
    int tablist[MAXTABNO];

    //int tablist[] = {10, 20, 40, 0};
    /* //testing findnexttab */
    /* int *nexttab; */
    /* int nexttabpos; */
    
    /* for (int i = 0; i < 100; i++) { */
    /*   nexttab = findnexttab(i, tablist, NTAB, &nexttabpos); */
    /*   printf("%d: nextab(%d) = %ld, tabpos = %d\n", i, *nexttab, */
    /* 	   (nexttab-tablist), nexttabpos); */
    /* } */

    int tabmode = 0; // 0 detab, 1 entab
    if (strstr(*argv, "detab") != NULL)
      tabmode = 0;
    else if (strstr(*argv, "entab") != NULL)
      tabmode = 1;
    else {
      printf("warning: using default mode \"detab\"\n");
      printf("use command names detab or entab to aumatically select mode.\n");
      printf("used command: %s\n", *argv);
      tabmode = 0;
    }
    
    int i = 0;
    while (i  < MAXTABNO-1 && --argc > 0) {
      tablist[i] = atoi(*++argv);
      i++;
    }
    tablist[i] = ENDOFTABS; // close the list with termination

    
    while ((len = mygetline(line, MAXLINE)) > 0) {
      if (tabmode == 0)
        mydetab(etline, line, tablist, NTAB);
      else if (tabmode == 1)
	myentab(etline, line, tablist, NTAB);
      else {
	printf("detab/entab: unsupported mode");
	return -1;
      }
        printf("%s", etline);
    }
}

void myentab(char t[], char s[], int *tablist, int ntab)
{
    int i = 0;
    int j = 0;
    int ni = 0;
    int nj = 0;
    int *nexttab;
    int nexttabpos;
    
    while (s[i] != '\0') {
        if (s[i] == '\t') {
            nexttab = findnexttab(ni, tablist, ntab, &nexttabpos);
            nj = ni = nexttabpos;
            t[j++] = s[i++];
            if (*nexttab != ENDOFTABS)
                tablist = nexttab;
        }
        else if (s[i] == ' ') {
            while (s[i] == ' ') {
                ++i;
                ++ni;
            }
            if (s[i] == '\0') {
                t[j] = '\0';
                return;
            }
            else {
                nexttab = findnexttab(nj, tablist, ntab, &nexttabpos);
                //printf("-%d-",nj);
                while (nexttabpos <= ni) {
                    t[j++] = '\t';
                    nj = nexttabpos;
                    if (*nexttab != ENDOFTABS)
                        tablist = nexttab;
                    nexttab = findnexttab(nj, tablist, ntab, &nexttabpos);
                }
                while (nj < ni) {
                    t[j++] = ' ';
                    nj++;
                }
            }
        }
        else {
            t[j++] = s[i++];
            ++ni;
            ++nj;
        }
    }
    t[j] = '\0';
}

void mydetab(char *t, char *s, int *tablist, int ntab)
{
    int i = 0;
    int j = 0;
    int n2t;
    
    for (i = j = 0; s[i] != '\0'; i++) {
        if (s[i] != '\t')
            t[j++] = s[i];
        else {
            while (*tablist != ENDOFTABS && *tablist <= j)
                tablist++;
            if (*tablist == ENDOFTABS)
                n2t = (ntab - (j % ntab));
            else
                n2t = (*tablist - j);
            while (n2t-- > 0)
                t[j++] = ' ';
        }
    }
    t[j] = '\0';
}

// findnexttab: find next tab after cursor in a list terminated with
// zero return a pointer to the list of tabs or NULL if the list is
// finished the cursor position of the next tab is provided via the
// pointer nexttabpos whether the list is still full or defaut tabbing
// is being used instead
int *findnexttab(int curspos, int *tablist, int ntab, int *nexttabpos)
{
    while (*tablist != ENDOFTABS && *tablist <= curspos)
        tablist++;
    if (*tablist == ENDOFTABS)
        *nexttabpos = curspos - curspos % ntab + ntab;
    else 
        *nexttabpos = *tablist;
    return tablist;
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
