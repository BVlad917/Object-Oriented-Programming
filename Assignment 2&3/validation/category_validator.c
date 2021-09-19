//
// Created by VladB on 12-Mar-21.
//

#include "category_validator.h"

int validate_category(int category) {
    if ((category < 1 || category > 4) && category != -1) {
        return 1;
    }
    return 0;
}