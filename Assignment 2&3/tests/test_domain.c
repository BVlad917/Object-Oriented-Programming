//
// Created by VladB on 07-Mar-21.
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "test_domain.h"
#include "../domain/date.h"
#include "../domain/product.h"

void test_date() {
    Date *d = create_date(17, 5, 2001);
    assert(get_date_day(d) == 17);
    assert(get_date_month(d) == 5);
    assert(get_date_year(d) == 2001);
    destroy_date(d);
}

void test_compare_dates() {
    Date *d = create_date(17, 5, 2001);
    Date *d1 = create_date(18, 5, 2001);

    assert(compare_dates(d, d1) < 0);
    assert(compare_dates(d1, d) > 0);

    Date *d2 = create_date(20, 6, 2003);
    assert(compare_dates(d2, d1) > 0);
    assert(compare_dates(d, d2) < 0);

    Date *d3 = create_date(20, 6, 2003);
    assert(compare_dates(d3, d1) != 0);
    assert(compare_dates(d3, d2) == 0);

    destroy_date(d3);
    destroy_date(d2);
    destroy_date(d1);
    destroy_date(d);
}

void test_nr_days_to_date() {
    time_t t = time(NULL);
    struct tm current_date = *localtime(&t);
    int current_day = current_date.tm_mday;
    int current_month = current_date.tm_mon + 1;
    int current_year = current_date.tm_year + 1900;
    Date *d = create_date(current_day + 1, current_month, current_year);
    assert(nr_days_to_date(d) == 1);
    destroy_date(d);
    d = create_date(current_day, current_month + 1, current_year);
    int days_to_date = nr_days_to_date(d);
    assert(days_to_date == 28 || days_to_date == 29 || days_to_date == 30 || days_to_date == 31);
    destroy_date(d);
    d = create_date(current_day, current_month, current_year + 1);
    assert(nr_days_to_date(d) == 364 || nr_days_to_date(d) == 365 || nr_days_to_date(d) == 366);
    destroy_date(d);
}

void test_product() {
    char *name = "Sugar\0";
    int category = 0;
    double quantity = 2.5;
    int day = 17, month = 5, year = 2001;
    Product *p = create_product(name, category, quantity, day, month, year);

    assert(strcmp(get_product_name(p), p->name) == 0);
    assert(get_product_category(p) == 0);
    assert(get_product_date(p)->day == 17);
    assert(get_product_date(p)->month == 5);
    assert(get_product_date(p)->year == 2001);
    assert(fabs(get_product_quantity(p) - quantity) < 0.000001);

    // Test the quantity setter
    set_product_quantity(p, 5.15);
    assert(fabs(get_product_quantity(p) - 5.15) < 0.00001);

    // Test the expiration info getters
    assert(get_product_expiration_day(p) == 17);
    assert(get_product_expiration_month(p) == 5);
    assert(get_product_expiration_year(p) == 2001);

    destroy_product(p);
}

void run_all_domain_tests() {
    printf("Starting domain tests...\n");
    test_date();
    test_nr_days_to_date();
    test_compare_dates();
    test_product();
    printf("Domain tests done.\n");
}