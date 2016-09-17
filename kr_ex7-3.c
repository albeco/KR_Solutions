#include <stdio.h>
#include <ctype.h>

void minprintf(char *fmt, ...);

int main(void)
{
  minprintf("%5.d\n", 10);
  minprintf("%3s: %4.3f", "pi", 3.14);
  minprintf("%10.2g",6.7e-11);
  minprintf("%4.2s\n", "---");
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
      /* while (width-- > strlen(sval)) */
      /* 	putchar(' '); */
      /* while (*sval) */
      /* 	putchar(*sval++); */
      printf("%*.*s", width, prec, sval);
      break;
    default:
      putchar(*p);
      break;
    }
  }
  va_end(ap);
}
