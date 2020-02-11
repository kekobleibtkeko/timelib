#include <stdio.h>
#include <stdlib.h>

/**
  *  Timelib
  *
  *  Kleine Library für nützliche Zeitfunktionen.
  *
  *  Datum: 11.02.20        Autor: Alexander Thielker
**/

void input_date(int*, int*, int*);
int SichereIntEingabe(int, int);
int day_of_the_year(int, int, int);
int get_days_for_month(int, int);
int exists_date(int, int, int);
int is_leapyear(int);
int _valid_month_and_year(int, int);

int main()
{
    //printf("%i", exists_date(1,1,1));
    //rintf("%i", get_days_for_month(2,2020));

    int day = 0, month = 0, year = 0;
    input_date(&day, &month, &year);
    printf("%i, %i, %i\n", day, month, year);
    printf("Tag des Jahres: %i\n", day_of_the_year(day, month, year));
    printf("%i", get_days_for_month(1,2019));
    return 0;
}

void input_date(int* day, int* month, int* year)
{
    int lday = 0, lmonth = 0, lyear = 0;
    printf("Bitte geben sie das gewollte Jahr ein. ( > 1582)\n");
    lyear = SichereIntEingabe(1582, 3000000);
    printf("Bitte geben sie den gewollten Monat ein.\n (1 - 12)\n");
    lmonth = SichereIntEingabe(1,12);
    printf("Bitte geben sie den gewollten Tag ein. (1 - %i)\n", get_days_for_month(lmonth, lyear));
    lday = SichereIntEingabe(1, get_days_for_month(lmonth, lyear));
    *day = lday;
    *month = lmonth;
    *year = lyear;
}

int day_of_the_year(int day, int month, int year)
{
    int total = 1;
    if (exists_date(day, month, year))
    {
            // jeweils die tage in den Monaten zum gesamt hinzuf�gen
        for (int i = 0; i < month; i++)
        {
            total += get_days_for_month(i, year);
        }
        return total += day; // die eingegebenen tage zum gesamt zuf�gen
    }
    return -1;
}

int get_days_for_month(int month, int year)
{
    int days[12] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (_valid_month_and_year(month, year))
    {
        days[1] = ((is_leapyear(year) == 1) // tage im februar setzen
                 ? 29
                 : 28);
        return days[month - 1];
    }
    return -1;
}

int _valid_month_and_year(int month, int year)
{
    return (year <= 2400 && year >= 1582
        && month >= 1 && month <= 12);
}

int exists_date(int day, int month, int year)
{
    return (_valid_month_and_year(month, year)
        && day >= 1 && day <= get_days_for_month(month, year));
}

int is_leapyear(int year)
{
    if (year <= 1581)
    {
        return -1;
    }
    else
    {
        return ((year%4 == 0
            && ((year%100 == 0 && year%400 == 0)
            ||(year%100 != 0)))); //abfrage
    }
}

int SichereIntEingabe(int aMin, int aMax)
{
    ///�berpr�ft die eingabe und wiederholt bei falscheingaben
    int eingabe = aMin - 1;
    while (eingabe < aMin)
    {
        if (scanf("%d",&eingabe))
        {
            if (eingabe <= aMax && eingabe >= aMin)
            {
                return eingabe;
            }
            else if (eingabe < aMin)
            {
                printf("Die Zahl muss groesser als %i sein.\n", aMin - 1);
            }
            else
            {
                printf("Die Zahl muss kleiner als %i sein.\n", aMax + 1);
            }
        }
        eingabe = aMin - 1;
        fflush(stdin);
    }
    return eingabe;
}
