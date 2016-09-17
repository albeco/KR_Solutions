#include <stdio.h>
#define MAXSTRING 80

/* expand(s1,s2) expands shorthand notations a-z, a-b-c, az0-9, -a-z */
void expand(char to[], char from[]);
int isseq(char a, char b); // if sequence like a-z or 1-9
int mygetline(char line[], int maxlength);

int main()
{
    char s[80], t[80];
    
    while (mygetline(t, MAXSTRING) > 0) {
        expand(s, t);
        printf("%s\n", s);
    }
    return 0;
}

void expand(char s[], char t[])
{
    int i, j;
    char c;
    
    i = j = 0;
    
    if (t[0] == '-')
        s[0] = '-', i++, j++;
    while (t[i] != '\0') {
      if (t[i] == '-' && isseq(t[i-1], t[i+1])) {
            if (t[i-1] == t[i+1])
                s[j++] = t[i+1];
            else
                for (c = t[i-1]+1; c <= t[i+1]; c++)
                    s[j++] = c;
            i += 2;
        }
        else
            s[j++] = t[i++];
    }
    s[j] = '\0';
}

int isseq(char x, char y)
{
    if (y < x)
        return 0;
    else if ((x >= 'a' && x <= 'z' && y <= 'z') ||
             (x >= 'A' && x <= 'Z' && y <= 'Z') ||
             (x >= '0' && x <= '9' && y <= '9'))
        return 1;
    else
        return 0;
}

/* getilne: read a line into s, return its length */
int mygetline(char s[], int lim)
{
    int c, i;
    
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') { 
        s[i] = c; // since the for loop exit before putting the newline
        ++i;
    }
    s[i] = '\0'; // the end of string character
    return i;
}
