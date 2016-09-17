#include <stdio.h>

#define MAXLINE 100

/* myatof: convert string s to double */

int mygetline(char s[], int lim);
int myisspace(char c);
int myisdigit(char c);

int main()
{
    double sum, myatof(char []);
    char line[MAXLINE];
    
    sum = 0.0;
    while (mygetline(line, MAXLINE) > 0)
        sum += myatof(line);
    printf("= %10.3g\n", sum);
}

double myatof(char s[])
{
  double val, power;
    int i, sign;
    
    for (i = 0; myisspace(s[i]); i++)
        ; /* skipping spaces */
    if (s[i] == '-')
        sign = -1, i++;
    else if (s[i] == '+')
        sign = +1, i++;
    else
        sign = +1;
    for (val = 0.0; myisdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.') {
        i++;
        for (power = 10.0; myisdigit(s[i]); i++) {
            val += (s[i] - '0') / power;
            power *= 10.0;
        }
    }
    if (s[i] == 'e' || s[i] == 'E') {
      i++;
      for (power = 0; myisdigit(s[i]); i++)
	power = 10 * power + (s[i] - '0');
      while (power-- > 0)
	val *= 10;
    }
    return sign * val;
}


/* getilne: read a line into s, return its length */
int mygetline(char s[], int lim)
{
    int c = '\0', i = 0;
    
    for (i = 0; (i < lim-1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
        s[i] = c;
    
    if (c == '\n') {
        s[i] = c; // since the for loop exit before putting the newline
        ++i;
    }
    s[i] = '\0'; // the end of string character
    return i;
}

int myisspace(char c)
{
    if (c == ' ' || c == '\t')
        return 1;
    else
        return 0;
}

int myisdigit(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    else
        return 0;
}
