#include <stdio.h>
#include <stdlib.h>

/**
  *  Tag des Jahres
  *
  *  Program, um zu berechnene der wie vielte Tag des Jahres die Eingabe ist
  *
  *  Datum: 14.01.20        Autor: Alexander Thielker
**/

int SichereIntEingabe(int, int);
int day_of_the_year(int, int, int);
int get_days_for_month(int, int);
int exists_date(int, int, int);
int is_leapyear(int);
int valid_month_and_year(int, int);

int main()
{
    //printf("%i", exists_date(1,1,1));
    //rintf("%i", get_days_for_month(2,2020));
    printf("Tag des Jahres: %i\n", day_of_the_year(31, 12, 2018));
    return 0;
}

int day_of_the_year(int day, int month, int year)
{
    int total = 0;
    if (exists_date(day, month, year))
    {
            // jeweils die tage in den Monaten zum gesamt hinzufügen
        for (int i = 0; i < month - 1; i++)
        {
            total += get_days_for_month(i, year);
        }
        return total += day; // die eingegebenen tage zum gesamt zufügen
    }
    return -1;
}

int get_days_for_month(int month, int year)
{
    int days[12] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (valid_month_and_year(month, year))
    {
        days[1] = ((is_leapyear(year) == 1) // tage im februar setzen
                 ? 29
                 : 28);
        return days[month - 1];
    }
    return -1;
}

int valid_month_and_year(int month, int year)
{
    return (year <= 2400 && year >= 1582
        && month >= 1 && month <= 12);
}

int exists_date(int day, int month, int year)
{
    return (valid_month_and_year(month, year)
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
    ///überprüft die eingabe und wiederholt bei falscheingaben
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
}



