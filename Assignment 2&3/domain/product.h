//
// Created by VladB on 07-Mar-21.
//

#ifndef A23_BVLAD917_PRODUCT_H
#define A23_BVLAD917_PRODUCT_H

#include "date.h"

/// We accept the following convention for the categories of <Product>:
///         1 - Dairy
///         2 - Sweets
///         3 - Meat
///         4 - Fruit
typedef struct {
    char *name;
    int category;
    double quantity;
    Date *date;
} Product;

/// Creates an instance of Product (with the given name, category, quantity, day, month, and year)
/// and returns a pointer to this instance.
Product *create_product(char *name, int category, double quantity, int day, int month, int year);

/// Frees the memory pointed to by the given product pointer. Also frees the memory used by the product's date.
void destroy_product(Product *p);

/// Returns a pointer to the name of the product.
char *get_product_name(Product *p);

/// Returns the product category as an integer (according to the above convention)
int get_product_category(Product *p);

/// Returns the product quantity as a double
double get_product_quantity(Product *p);

/// Sets the product quantity to the given <new_quantity>
void set_product_quantity(Product *p, double new_quantity);

/// Returns a pointer to the product's date
Date *get_product_date(Product *p);

/// Returns the product expiration day as an integer
int get_product_expiration_day(Product *p);

/// Returns the product expiration month as an integer
int get_product_expiration_month(Product *p);

/// Returns the product expiration year as an integer
int get_product_expiration_year(Product *p);

#endif //A23_BVLAD917_PRODUCT_H
