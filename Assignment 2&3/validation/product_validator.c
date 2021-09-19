//
// Created by VladB on 07-Mar-21.
//

#include <string.h>

#include "product_validator.h"
#include "date_validator.h"

int validate_product(Product *p) {
    int error = 1, category;
    double quantity;
    if (strlen(get_product_name(p)) == 0) {
        error *= 3;
    }
    category = get_product_category(p);
    if (category != 1 && category != 2 && category != 3 && category != 4) {
        error *= 5;
    }
    quantity = get_product_quantity(p);
    if (quantity < 0) {
        error *= 7;
    }
    if (validate_date(get_product_date(p))) {
        error *= 11;
    }

    if (error > 1) {
        error = -error;
    } else {
        error = 0;
    }
    return error;
}