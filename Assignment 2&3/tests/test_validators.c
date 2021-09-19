//
// Created by VladB on 07-Mar-21.
//

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "test_validators.h"
#include "../domain/date.h"
#include "../validation/date_validator.h"
#include "../domain/product.h"
#include "../validation/product_validator.h"

void test_validate_date() {
    int day = 17, month = 5, year = 2001, valid;
    Date *d = create_date(day, month, year);
    assert(validate_date(d) == 0);
    destroy_date(d);

    day = 0;
    d = create_date(day, month, year);
    valid = validate_date(d);
    assert(valid < 0);
    assert(valid % 3 == 0);
    assert(valid % 5 != 0);
    assert(valid % 7 != 0);
    destroy_date(d);

    day = 17, month = 22;
    d = create_date(day, month, year);
    valid = validate_date(d);
    assert(valid < 0);
    assert(valid % 3 != 0);
    assert(valid % 5 == 0);
    assert(valid % 7 != 0);
    destroy_date(d);

    month = 5, year = 30;
    d = create_date(day, month, year);
    valid = validate_date(d);
    assert(valid < 0);
    assert(valid % 3 != 0);
    assert(valid % 5 != 0);
    assert(valid % 7 == 0);
    destroy_date(d);

    day = -1, month = 33, year = 2001;
    d = create_date(day, month, year);
    valid = validate_date(d);
    assert(valid < 0);
    assert(valid % 3 == 0);
    assert(valid % 5 == 0);
    assert(valid % 7 != 0);
    destroy_date(d);

    day = -1, month = 12, year = -2001;
    d = create_date(day, month, year);
    valid = validate_date(d);
    assert(valid < 0);
    assert(valid % 3 == 0);
    assert(valid % 5 != 0);
    assert(valid % 7 == 0);
    destroy_date(d);

    day = 17, month = 13, year = -2001;
    d = create_date(day, month, year);
    valid = validate_date(d);
    assert(valid < 0);
    assert(valid % 3 != 0);
    assert(valid % 5 == 0);
    assert(valid % 7 == 0);
    destroy_date(d);

    day = 200, month = 13, year = -2001;
    d = create_date(day, month, year);
    valid = validate_date(d);
    assert(valid < 0);
    assert(valid % 3 == 0);
    assert(valid % 5 == 0);
    assert(valid % 7 == 0);
    destroy_date(d);

    // Check leap years
    day = 29, month = 2, year = 2020;
    d = create_date(day, month, year);
    assert(validate_date(d) == 0);
    destroy_date(d);

    day = 29, month = 2, year = 2021;
    d = create_date(day, month, year);
    assert(validate_date(d) < 0);
    destroy_date(d);
}

void test_validate_product() {
    char name[256] = "Sugar";
    int cat = 1;
    double quantity = 2.5;
    int day = 17, month = 5, year = 2001;
    Product *p = create_product(name, cat, quantity, day, month, year);
    assert(validate_product(p) == 0);
    destroy_product(p);

    strcpy(name, "");
    p = create_product(name, cat, quantity, day, month, year);
    assert(validate_product(p) < 0);
    assert(validate_product(p) % 3 == 0);
    destroy_product(p);

    strcpy(name, "Salt");
    cat = 9;
    p = create_product(name, cat, quantity, day, month, year);
    assert(validate_product(p) < 0);
    assert(validate_product(p) % 5 == 0);
    destroy_product(p);

    cat = 2;
    quantity = -1.1;
    p = create_product(name, cat, quantity, day, month, year);
    assert(validate_product(p) < 0);
    assert(validate_product(p) % 7 == 0);
    destroy_product(p);

    quantity = 3.31;
    day = 500;
    p = create_product(name, cat, quantity, day, month, year);
    assert(validate_product(p) < 0);
    assert(validate_product(p) % 11 == 0);
    destroy_product(p);

    day = 13;
    p = create_product(name, cat, quantity, day, month, year);
    assert(validate_product(p) == 0);
    destroy_product(p);
}

void run_all_validators_tests() {
    printf("Starting validators tests...\n");
    test_validate_date();
    test_validate_product();
    printf("Validators tests done.\n");
}