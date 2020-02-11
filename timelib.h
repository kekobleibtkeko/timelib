#ifndef TIMELIB_H_INCLUDED
#define TIMELIB_H_INCLUDED

void input_date(int* day, int* month, int* year);
int day_of_the_year(int day, int month, int year);
int get_days_for_month(int month, int year);
int exists_date(int day, int month, int year);
int is_leapyear(int year);

int get_weekday(int day, int month, int year);
int get_calender_week(int day, int month, int year);


int _valid_month_and_year(int, int);
int _SichereIntEingabe(int, int);
void _print_weekday(int);
int _week_day_beginning(int);

#endif // TIMELIB_H_INCLUDED
