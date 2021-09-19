//
// Created by VladB on 07-Mar-21.
//

#ifndef A23_BVLAD917_DATE_H
#define A23_BVLAD917_DATE_H

typedef struct {
    int day;
    int month;
    int year;
} Date;

/// Creates an instance of Date with given day, month, and year and returns a pointer to this instance
Date *create_date(int day, int month, int year);

/// Frees the memory used by the instance of Date pointed to by the given date pointer
void destroy_date(Date *d);

/// Returns the date day as an integer
int get_date_day(Date *d);

/// Returns the date month as an integer
int get_date_month(Date *d);

/// Returns the date year as an integer
int get_date_year(Date *d);

/// Returns the number of days (from the current time) until the given date
int nr_days_to_date(Date *d);

/// Compares 2 dates.
/// If the date <d1> is further into the future than date <d2> then the function returns 1.
/// If the 2 dates are actually the same date, then the function returns 0.
/// If the date <d2> is further into the future than date <d1> then the function returns -1.
int compare_dates(Date *d1, Date *d2);

#endif //A23_BVLAD917_DATE_H
