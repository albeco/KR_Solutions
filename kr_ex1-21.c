//
//  main.c
//  testcproject
//
//  Created by Alberto Comin on 11/02/15.
//  Copyright (c) 2015 albeco. All rights reserved.
//

#include <stdio.h>

#include <stdio.h>
#define MAXLINE 1000 // max input line length
#define NTAB 8

// detab: replaces tabs with spaces, assuming a tab every N columns
// entab: replaces blanks with tabs and min no. of blanks

int mygetline(char line[], int maxline);
void mydetab(char detabbed[], char tabbed[], int ntab);
void myentab(char entabbed[], char line[], int ntab);


// reverse input one line at time
int main()
{
    int len;
    char line[MAXLINE];
    char etline[MAXLINE];
    
    while ((len = mygetline(line, MAXLINE)) > 0) {
        myentab(etline, line, NTAB);
        //int i = 0;
        //while (etline[i] != '\0') {
        //if (etline[i] == '\t')
        //printf("\\t");
        //else
        //putchar(etline[i]);
        // ++i;
        // }
        printf("%s", etline);
    }
}

void myentab(char t[], char s[], int ntab)
{
    int i = 0;
    int j = 0;
    int ni = 0;
    int nj = 0;
    
    int ntabs = 0;
    
    while (s[i] != '\0') {
        if (s[i] == '\t') {
            t[j++] = s[i++];
            ni += (ntab - (ni % ntab));
            nj += (ntab - (nj % ntab));
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
                ntabs = ni / ntab - nj / ntab;
                while (ntabs-- > 0) {
                    t[j++] = '\t';
                    nj += (ntab - (nj % ntab));
                }
                while (nj < ni) {
                    t[j++] = ' ';
                    ++nj;
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

void mydetab(char t[], char s[], int ntab)
{
    int i = 0;
    int j = 0;
    
    while (s[i] != '\0') {
        if (s[i] != '\t')
            t[j++] = s[i++];
        else {
            ++i;
            t[j++] = ' ';
            while ((j % ntab) != 0)
                t[j++] = ' ';
        }
    }
    t[j] = '\0';
}


int mygetline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c =='\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
