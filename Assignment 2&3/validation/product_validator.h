//
// Created by VladB on 07-Mar-21.
//

#ifndef A23_BVLAD917_PRODUCT_VALIDATOR_H
#define A23_BVLAD917_PRODUCT_VALIDATOR_H

#include "../domain/product.h"

/// Validates the product given by the pointer <p>
/// \return: an integer - 0 if the date is valid
///                     - a negative number if the given date is not valid, as such:
///                             -> divisible by 3 if the name is not valid
///                             -> divisible by 5 if the category is not valid
///                             -> divisible by 7 if the quantity is not valid
///                             -> divisible by 11 if the date is not valid
int validate_product(Product *p);

#endif //A23_BVLAD917_PRODUCT_VALIDATOR_H
