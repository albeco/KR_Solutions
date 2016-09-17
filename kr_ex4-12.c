#include <stdio.h>

int itoa(int n, char s[]);

int main(void)
{
    int n = 1;
    int narg = 1;
    char s[100];
    while (narg == 1)
    {
        printf("n: ");
        narg = scanf("%d",&n);
        if (narg == 1) {
            itoa(n, s);
	    printf("\t%s\n", s);
	}
    }
    return 0;
}

int itoa(int n, char s[])
{
    int i = 0;
    if (n / 10)
        i = itoa(n/10, s);
    else if (n < 0) 
        s[i++] = '-';
    s[i++] = ((n > 0 ? n : -n) % 10) + '0';
    s[i] = '\0';
    return i;
}
