//
// Created by VladB on 07-Mar-21.
//

#ifndef A23_BVLAD917_DATE_VALIDATOR_H
#define A23_BVLAD917_DATE_VALIDATOR_H


#include "../domain/date.h"

/// Validates the date given by the pointer <d>.
/// \return: an integer - 0 if the date is valid
///                     - a negative number if the given date is not valid, as such:
///                             -> divisible by 3 if the day is not valid
///                             -> divisible by 5 if the month is not valid
///                             -> divisible by 7 if the year is not valid
int validate_date(Date *d);

#endif //A23_BVLAD917_DATE_VALIDATOR_H
