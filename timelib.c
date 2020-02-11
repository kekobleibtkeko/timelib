#include <stdio.h>

/**
  *  Timelib
  *
  *  Kleine Library für nützliche Zeitfunktionen.
  *
  *  Datum: 11.02.20        Autor: Alexander Thielker
**/

/**
    Die Funktion liest 3 Ganzzahlwerte (Integer) ein, für Tag, Monat und Jahr. Wenn das angegebene Datum
    ungültig ist, wird erneut eingelesen, solange bis ein gültiges Datum eingegeben wurde
**/
void input_date(int* day, int* month, int* year)
{
    int lday = 0, lmonth = 0, lyear = 0;
    printf("Bitte geben sie das gewollte Jahr ein. ( > 1582)\n");
    lyear = _SichereIntEingabe(1582, 2400);
    printf("Bitte geben sie den gewollten Monat ein.\n (1 - 12)\n");
    lmonth = _SichereIntEingabe(1,12);
    printf("Bitte geben sie den gewollten Tag ein. (1 - %i)\n", get_days_for_month(lmonth, lyear));
    lday = _SichereIntEingabe(1, get_days_for_month(lmonth, lyear));
    *day = lday;
    *month = lmonth;
    *year = lyear;
}

/**
    Die Funktion berechnet für ein gegebenes Datum des gregorianischen Kalenders bestehend aus Tag, Monat
    und Jahr die Nummer des Tages, gezählt von Jahresbeginn (1. Januar) an. Schaltjahre werden bei der
    Berechnung berücksichtigt. Ist das übergebene Datum ungültig, beträgt der Rückgabewert -1.
**/
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

/**
    Die Funktion bestimmt für einen gegebenen Monat eines gegebenen Jahres, wie viele Tage der Monat hat. Der
    Wert des Monats muss zwischen 1 und 12 liegen. Schaltjahre werden berücksichtigt
**/
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

/**
    Die Funktion gibt den Wochentag vom Jahresanfang wieder
    0 = Sonntag, 1 = Montag, 2 = Dienstag, ... 6 = Samstag
**/
int _week_day_beginning(int year)
{
    return ((1 + 5 * ((year - 1) % 4) + 4 * ((year - 1) % 100) + 6 * ((year - 1) % 400 )) % 7);
}

/**
    Gibt 1 wieder, wenn die eingegebenen Daten Valide sind, 0 wenn nicht
    der Monat muss zwischen 1 un 12 liegen, das Jahr zwischen 1582 und 2400
**/
int _valid_month_and_year(int month, int year)
{
    return (year <= 2400 && year >= 1582
        && month >= 1 && month <= 12);
}

/**
    Die Funktion überprüft, ob ein eingegebenes Datum gültig ist. Daten vor dem 1.1.1582 sind ungültig, genauso
    wie alle Daten nach dem 31.12.2400.
**/
int exists_date(int day, int month, int year)
{
    return (_valid_month_and_year(month, year)
        && day >= 1 && day <= get_days_for_month(month, year));
}

/**
    Die Funktion überprüft, ob ein gegebenes Jahr nach den Regeln des gregorianischen Kalender ein Schaltjahr
    ist. Bei Jahreszahlen vor dem Jahr 1582 wird ein Fehler zurückgegeben.
**/
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

/**
    Gibt den Wochentag für den gewählten Tag wieder.
    0 = Sonntag, 1 = Montag, ... 6 = Samstag
**/
int get_weekday(int day, int month, int year)
{
    int current = day_of_the_year(day, month, year) - 1;
    return (current + _week_day_beginning(year)) % 7;
}

/**
    Gibt den gewählten Wochentag im Format von get_weekday() aus.
**/
void _print_weekday(int day)
{
    switch (day)
    {
    default:
        printf("INVALID DAY");
        break;
    case 0:
        printf("Sonntag");
        break;
    case 1:
        printf("Montag");
        break;
    case 2:
        printf("Dienstag");
        break;
    case 3:
        printf("Mittwoch");
        break;
    case 4:
        printf("Donnerstag");
        break;
    case 5:
        printf("Freitag");
        break;
    case 6:
        printf("Samstag");
        break;

    }
}

/**
    Gibt für das gewählte Datum die Kalenderwoche aus.
    Wenn diese nicht ins gwählte Jahr fällt so gebe man 52 zurück.
**/
int get_calender_week(int day, int month, int year)
{
    int currentDays = day_of_the_year(day, month, year);
    int startWeekDay = _week_day_beginning(year);
    int calenderWeek = (currentDays / 7) + (startWeekDay < 4);
    return (calenderWeek == 0)
        ? 52
        : calenderWeek;
}

/**
    Lässt den Nutzer eine Zahl zwischen aMin un aMax eingeben,
    ist die Zahl zu groß oder zu klein oder ist die Eingabe keine Zahl,
    bekommt der Nutzer wieder die Gelegenheit die Zahl neu
    einzulesen, bis die Eingabe passt.
**/
int _SichereIntEingabe(int aMin, int aMax)
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
