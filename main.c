#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"


int main()
{
    //printf("%i", exists_date(1,1,1));
    //rintf("%i", get_days_for_month(2,2020));

    int day = 0, month = 0, year = 0;
    input_date(&day, &month, &year);

    printf("%i, %i, %i\n", day, month, year);

    printf("Wochentag (Jahresbeginn): ");
    _print_weekday(_week_day_beginning(year));
    printf("\n");

    printf("Wochentag: ");
    _print_weekday(get_weekday(day, month, year));
    printf("\n");

    printf("Kalenderwoche: %i\n", get_calender_week(day, month, year));
    printf("Tag des Jahres: %i\n", day_of_the_year(day, month, year));

    return 0;
}
