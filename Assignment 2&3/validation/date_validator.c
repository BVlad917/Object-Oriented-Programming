//
// Created by VladB on 07-Mar-21.
//

#include "date_validator.h"

#define MAX_YEAR 3000
#define MIN_YEAR 1900

/// Checks if the given year is a leap year or not
/// \return: 1 if the given year is a leap year; 0 otherwise
int is_leap_year(int year) {
    if (year % 400 == 0) {
        return 1;
    }
    if (year % 100 == 0) {
        return 0;
    }
    if (year % 4 == 0) {
        return 1;
    }
    return 0;
}

int validate_date(Date *d) {
    int error = 1;
    int y = get_date_year(d);
    int m = get_date_month(d);
    int zi = get_date_day(d);

    // Check if the year is outside of the available range
    if (y < MIN_YEAR || y > MAX_YEAR) {
        error *= 7;
    }
    // Check if the month is in the range [1, 12]
    if (m < 1 || m > 12) {
        error *= 5;
    }
    // Check if the day is in the range [1, 31]
    if (zi < 1 || zi > 31) {
        error *= 3;
    } else {
        // Edge case for February
        if (m == 2) {
            if ((is_leap_year(y) == 1 && zi > 29) || (is_leap_year(y) == 0 && zi > 28)) {
                error *= 3;
            }
        }
            // Checking if the day is within the range allowed by that month
        else {
            if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && zi > 31) {
                error *= 3;
            }
            if ((m == 4 || m == 6 || m == 9 || m == 11) && zi > 30) {
                error *= 3;
            }
        }
    }

    if (error > 1) {
        error = -error;
    } else {
        error = 0;
    }
    return error;
}