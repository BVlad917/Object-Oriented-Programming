//
// Created by VladB on 15-Mar-21.
//

#include <string.h>
#include <ctype.h>

#include "comparators_and_filters.h"

int descending_name_comp(const void *a, const void *b) {
    Product *p1 = *((Product **) a);
    Product *p2 = *((Product **) b);
    if (strcmp(get_product_name(p1), get_product_name(p2)) < 0) {
        return 1;
    } else if (strcmp(get_product_name(p1), get_product_name(p2)) == 0) {
        return 0;
    }
    return -1;
}

int ascending_name_comp(const void *a, const void *b) {
    Product *p1 = *((Product **) a);
    Product *p2 = *((Product **) b);
    if (strcmp(get_product_name(p1), get_product_name(p2)) > 0) {
        return 1;
    } else if (strcmp(get_product_name(p1), get_product_name(p2)) == 0) {
        return 0;
    }
    return -1;
}

int ascending_quantity_comp(const void *a, const void *b) {
    Product *p1 = *((Product **) a);
    Product *p2 = *((Product **) b);
    if (get_product_quantity(p1) > get_product_quantity(p2)) {
        return 1;
    }
    return -1;
}

int ascending_expiration_comp(const void *a, const void *b) {
    Product *p1 = *((Product **) a);
    Product *p2 = *((Product **) b);
    if (compare_dates(get_product_date(p1), get_product_date(p2)) > 0) {
        return 1;
    } else if (compare_dates(get_product_date(p1), get_product_date(p2)) < 0) {
        return -1;
    }
    return 0;
}

int descending_expiration_comp(const void *a, const void *b) {
    Product *p1 = *((Product **) a);
    Product *p2 = *((Product **) b);
    if (compare_dates(get_product_date(p1), get_product_date(p2)) < 0) {
        return 1;
    } else if (compare_dates(get_product_date(p1), get_product_date(p2)) > 0) {
        return -1;
    }
    return 0;
}

int string_filter(Product *p, char *str) {
    // If an empty string is given (or the newline character was caught from the buffer) then
    // we automatically consider that the product name matches the give string
    if (strlen(str) == 0 || (strlen(str) == 1 && str[0] == '\n')) {
        return 1;
    }
    char filter_string[256], product_name[256];
    strcpy(filter_string, str);
    strcpy(product_name, get_product_name(p));
    for (int i = 0; filter_string[i]; i++) {
        filter_string[i] = (char) tolower(filter_string[i]);
    }
    for (int i = 0; product_name[i]; i++) {
        product_name[i] = (char) tolower(product_name[i]);
    }
    if (strstr(product_name, filter_string) != NULL) {
        return 1;
    }
    return -1;
}

int category_filter(Product *p, int category) {
    if (get_product_category(p) == category) {
        return 1;
    }
    return -1;
}

int expiration_date_filter(Product *p, int expire_in) {
    if (nr_days_to_date(get_product_date(p)) <= expire_in) {
        return 1;
    }
    return -1;
}

int less_than_quantity_filter(Product *p, double quantity) {
    if (get_product_quantity(p) < quantity) {
        return 1;
    }
    return -1;
}

int greater_than_quantity_filter(Product *p, double quantity) {
    if (get_product_quantity(p) > quantity) {
        return 1;
    }
    return -1;
}