#include <stdio.h>
#define MAXLINE 1000

int mygetline(char line[], int maxline);
int strindex(char source[], char searchfor[]);

char pattern[] = "cake";

/* find all lines matching pattern, searching backwards */
int main()
{
    char line[MAXLINE];
    int found = 0;
    int pos;
    
    while (mygetline(line, MAXLINE) > 0)
        if ((pos = strindex(line, pattern)) >= 0) {
            printf("(%d)%s", pos, line);
            found++;
        }
    return found;
}

/* mygetline: get line into s, return length */
int mygetline(char s[], int lim)
{
    int c, i;
    
    i = c = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* strindex: return index of t is s, -1 if none */
int strindex(char s[], char t[])
{
    int i, j, k;
    int lens, lent;

    for (lens=0; s[lens] != '\0'; lens++)
      ;
    for (lent=0; t[lent] != '\0'; lent++)
      ;
    if (lens < lent)
      return -1;
    
    
    for (i = lens - lent; s[i] != '\0'; --i) {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}
