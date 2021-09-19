//
// Created by VladB on 15-Mar-21.
//

#ifndef A23_BVLAD917_COMPARATORS_AND_FILTERS_H
#define A23_BVLAD917_COMPARATORS_AND_FILTERS_H

#include "../domain/product.h"

/* =========== COMPARATORS =========== */

/// Comparator used for sorting products from a dynamic array in descending order by name
int descending_name_comp(const void *a, const void *b);

/// Comparator used for sorting products from a dynamic array in ascending order by name
int ascending_name_comp(const void *a, const void *b);

/// Comparator used for sorting products from a dynamic array in ascending order by quantity
int ascending_quantity_comp(const void *a, const void *b);

/// Comparator used for sorting products from a dynamic array in ascending order of their expiration date
/// (So the products which expire further into the future are sorted in the last positions)
int ascending_expiration_comp(const void *a, const void *b);

/// Comparator used for sorting products from a dynamic array in descending order of their expiration date
/// (So the products which expire further into the future are sorted in the first positions)
int descending_expiration_comp(const void *a, const void *b);



/* =========== FILTERS =========== */

/// Filter used for selecting the products in a dynamic array which contain the string <str> in their name
int string_filter(Product *p, char* str);

/// Filter used for selecting the products in a dynamic array which are of category <category>
int category_filter(Product *p, int category);

/// Filter used for selecting the products in a dynamic array which expire in at most <expire_in> days
int expiration_date_filter(Product *p, int expire_in);

/// Filter used for selecting the products in a dynamic array which have a quantity smaller than <quantity>
int less_than_quantity_filter(Product *p, double quantity);

/// Filter used for selecting the products in a dynamic array which have a quantity greater than <quantity>
int greater_than_quantity_filter(Product *p, double quantity);

#endif //A23_BVLAD917_COMPARATORS_AND_FILTERS_H
