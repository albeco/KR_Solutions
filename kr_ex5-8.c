#include <stdio.h>
#define test_doy(y,m,d) printf("year: %d, month: %d, day: %d, D: %d\n", y,m,d,day_of_year(y,m,d))

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);
void test_calendar(int, int, int);

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
  printf("year: %d, month: %d, day: %d, day of year: %d\n", y, m, d, doy);
  month_day(y, doy, &mm, &dd);
  printf("mm: %d, dd: %d\n\n", mm, dd);
}

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
  
/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
  int i, leap;
  
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
    for(i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;

  leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
  
  if (year < -5000 || year > 5000) {
    printf("valid years: 5000ac - 5000bc\n");
    //return -1;
  }
  if (yearday < 1 || yearday > 366+leap) {
    printf("valid yearday: 1 - %d\n", 365+leap);
    //return -1;
  }
  
  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;
  return;
}
