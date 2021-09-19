//
// Created by VladB on 07-Mar-21.
//

#include <stdlib.h>
#include <string.h>

#include "product.h"

Product *create_product(char *name, int category, double quantity, int day, int month, int year) {
    Product *p = (Product *) malloc(sizeof(Product));
    p->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(p->name, name);
    p->category = category;
    p->quantity = quantity;
    p->date = create_date(day, month, year);
    return p;
}

void destroy_product(Product *p) {
    free(p->name);
    destroy_date(p->date);
    free(p);
}

char* get_product_name(Product *p) {
    return p->name;
}

int get_product_category(Product *p) {
    return p->category;
}

double get_product_quantity(Product *p) {
    return p->quantity;
}

Date *get_product_date(Product *p) {
    return p->date;
}

int get_product_expiration_day(Product *p) {
    return get_date_day(p->date);
}

int get_product_expiration_month(Product *p) {
    return get_date_month(p->date);
}

int get_product_expiration_year(Product *p) {
    return get_date_year(p->date);
}

void set_product_quantity(Product *p, double new_quantity) {
    p->quantity = new_quantity;
}
