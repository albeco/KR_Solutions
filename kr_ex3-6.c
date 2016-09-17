#include <stdio.h>
#include <limits.h>


void itoa(int no, char str[], int size);

int main()
{
    int intno = 0;
    int n = 2;
    int i;
    int size = 10;
    char c,s[80];
    
    while (n > 0) {
        printf(">");
        if ((n = scanf("%d,%d", &intno, &size)) > 0) {
         itoa(intno, s, size);
            printf("%s\n", s);
        }
        else {
            i = 0; /* read unprocessed input left over by scanf */
            while ((s[i++] = c = getchar()) != '\n' && c != EOF)
                ;
            s[i] = '\0';
            printf("USAGE: number,size. Unprocessed part: \"%s\"\n", s);
        }
    }
}

void itoa(int n, char s[], int size) {
    int sign;
    int i = 0;
    int j;
    char c;
    
    if ((sign = n) >= 0) {
        s[i++] = n % 10 + '0';
        n /= 10;
    }
    else {
        s[i++] = -(n % 10) + '0';
        n /= -10;
    }
    while (n > 0) {
        s[i++] = n % 10 + '0';
        n /= 10;
    }
    if (sign < 0)
        s[i++] = '-';
    while (i < size)
        s[i++] = ' ';
    s[i--] = '\0';
    /* reversing string */
    for (j = 0; j < i; j++, i--)
        c = s[j], s[j] = s[i], s[i] = c;
}
