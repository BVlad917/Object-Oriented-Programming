//
// Created by VladB on 07-Mar-21.
//

#include <stdlib.h>
#include <time.h>

#include "date.h"

Date *create_date(int day, int month, int year) {
    Date *d = (Date *) malloc(sizeof(Date));
    d->day = day;
    d->month = month;
    d->year = year;
    return d;
}

void destroy_date(Date *d) {
    free(d);
}

int get_date_day(Date *d) {
    return d->day;
}

int get_date_month(Date *d) {
    return d->month;
}

int get_date_year(Date *d) {
    return d->year;
}

int nr_days_to_date(Date *d) {
    time_t t = time(NULL);
    // We initialize both dates to the current time (to avoid warnings)
    // We will change <away_date> to the given date <d>.
    struct tm current_date = *localtime(&t);
    struct tm away_date = *localtime(&t);

    away_date.tm_year = get_date_year(d) - 1900;
    away_date.tm_mon = get_date_month(d) - 1;
    away_date.tm_mday = get_date_day(d);
    away_date.tm_hour = 23;
    away_date.tm_min = 59;
    away_date.tm_sec = 59;

    time_t t1, t2;
    t2 = mktime(&away_date);
    t1 = mktime(&current_date);

    double diff_in_seconds = difftime(t2, t1);
    return (int) diff_in_seconds / (24 * 3600);
}

int compare_dates(Date *d1, Date *d2) {
    if (get_date_year(d1) > get_date_year(d2) ||
        (get_date_year(d1) == get_date_year(d2) && get_date_month(d1) > get_date_month(d2)) ||
        (get_date_year(d1) == get_date_year(d2) && get_date_month(d1) == get_date_month(d2) &&
         get_date_day(d1) > get_date_day(d2)))
        return 1;
    else if (get_date_year(d1) == get_date_year(d2) && get_date_month(d1) == get_date_month(d2) &&
             get_date_day(d1) == get_date_day(d2))
        return 0;
    return -1;
}