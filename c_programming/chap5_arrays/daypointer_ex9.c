#include <stdio.h>

static char year_month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char leap_year_month_days[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char *daytab[2] = {year_month_days, leap_year_month_days};

static int yeardays[2] = {365, 366};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
    int year, month, day, yearday;
    scanf("%d", &year);
    scanf("%d", &month);
    scanf("%d", &day);
    printf("%d\n", day_of_year(year, month, day));
    scanf("%d", &yearday);
    month_day(year, yearday, &month, &day);
    printf("%d %d\n", month, day);
}

int day_of_year(int year, int month, int day)
{
    if (year < 0) {
        printf("The year is a bc year, not support yet.\n");
        return -1;
    }
    if (month <= 0 || month >= 13) {
        printf("It's not a correct month, please check it.\n");
        return -1;
    }
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (day <= 0 || day > *(*(daytab+leap) + month)) {
        printf("The day is not a correct day, please check it.\n");
        return -1;
    }
    for (i = 1; i < month; i++)
        day += *(*(daytab+leap) + i);
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    if (year < 0) {
        printf("The year is a bc year, not support yet.\n");
    }
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (yearday <= 0 || yearday > yeardays[leap]) {
        printf("The yearday is not correct, please check it.\n");
    }
    for (i=1; yearday > *(*(daytab+leap) + i); i++)
        yearday -= *(*(daytab+leap) + i);
    *pmonth = i;
    *pday = yearday;
}
