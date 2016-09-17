#include <stdio.h>
#include <ctype.h>
#define STRLEN 100

int minscanf(char *fmt, ...);
void minprintf(char *fmt, ...);

int main(void)
{
    int n = 0;
    float x = 0.0;
    char s[STRLEN];
    int nread;
    
    for (n=0; n<STRLEN; n++)
        s[n] = '\0';
    n = 0;
    nread = minscanf("%d%s%e", &n, s, &x);
    
    printf("num arg: %d\n", nread);
    printf("n = %d, x = %e,  s = %s\n", n, x, s);
    
    return 0;
}

#include <stdarg.h>
#include <string.h>
// minprintf: minimal printf with printable argument list
void minprintf(char *fmt, ...)
{
    va_list ap; // points to each unnamed arg in turn
    char *p, *sval;
    int ival;
    double dval;
    int width = 0;
    int prec = 0;
    
    va_start(ap, fmt); // make ap point to 1st unnamed arg
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        if (isdigit(*++p)) {
            width = *p - '0';
            //width = atoi(p);
            while (isdigit(*++p))
                width = 10*width + (*p - '0');
            if (*p == '.') {
                prec = 0;
                while (isdigit(*++p))
                    prec = 10*prec + (*p - '0');
            }
        }
        switch (*p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%*.*d", width, prec, ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%*.*f", width, prec, dval);
                break;
            case 'g':
                dval = va_arg(ap, double);
                printf("%*.*g", width, prec, dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                printf("%*.*s", width, prec, sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}


int minscanf(char *fmt, ...)
{
    va_list ap;
    char *p;
    char *s;
    int *pint;
    float *pfloat;
    int width = 0, prec = 0, readval = 0;
    
    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%')
            continue;
        if (isdigit(*++p)) {
            width = *p - '0';
            //width = atoi(p);
            while (isdigit(*++p))
                width = 10*width + (*p - '0');
            if (*p == '.') {
                prec = 0;
                while (isdigit(*++p))
                    prec = 10*prec + (*p - '0');
            }
        }
        switch(*p) {
            case 'd':
                pint = va_arg(ap, int *);
                readval += scanf("%d", pint);
                break;
            case 'e':
                pfloat = va_arg(ap, float *);
                readval += scanf("%e", pfloat);
		break;
            case 's':
            default:
                s =  va_arg(ap, char *);
                readval += scanf("%s",  s );
                break;
        }
    }
    va_end(ap);
    return readval;
}
