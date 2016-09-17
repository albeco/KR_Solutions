#include <stdio.h>

/* version change: rewritten using pointers instead of indexing */

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);
void test_calendar(int, int, int);
char *monthname[] = { "illegal month name", "Jan", "Feb", "Mar", "Apr", "May",
"Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int main(void)
{
  test_calendar(2010,2,25);
  test_calendar(1990,2,27);
  test_calendar(1700,2,29);
  test_calendar(1980,3,12);
  test_calendar(1881,8,12);
  
  return 0;
}

void test_calendar(int y, int m, int d)
{
  int mm, dd;
  int doy = day_of_year(y,m,d);
  printf("year: %d, %s, %d, day of year: %d\n", y, monthname[m], d, doy);
  if (doy != -1) {
    month_day(y, doy, &mm, &dd);
    printf("year: %d, %s, %d\n\n", y, monthname[mm], dd);
  }
  else
    putchar('\n');
}

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
  
/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
  int leap;
  char *dp;
  
  if (month < 1 || month > 12) {
    printf("valid months: 1 - 12\n");
    return -1;
  }
  if (year < -5000 || year > 5000) {
    printf("valid years: 5000ac - 5000bc\n");
    return -1;
  }
  leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
  if (day < 1 || day > daytab[leap][month]) {
    printf("valid days: 1-%d\n", daytab[leap][month]);
    return -1;
  }
  
  dp = daytab[leap];
  while (--month > 0)
    day += *++dp; 
 
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;
  char  *dp;
  
  leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
  
  if (year < -5000 || year > 5000) {
    printf("valid years: 5000ac - 5000bc\n");
    //return -1;
  }
  if (yearday < 1 || yearday > 366+leap) {
    printf("valid yearday: 1 - %d\n", 365+leap);
    //return -1;
  }

  dp = daytab[leap];
  while (yearday > *++dp)
    yearday -= *dp;
  *pmonth = dp - daytab[leap];
  *pday = yearday;
  
  return;
}
