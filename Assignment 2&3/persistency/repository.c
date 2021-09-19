//
// Created by VladB on 07-Mar-21.
//

#include <stdlib.h>
#include <string.h>

#include "repository.h"

Repository *create_repository(int capacity) {
    Repository *repo = (Repository *) malloc(sizeof(Repository));
    repo->dyn_array = create_dynamic_array(capacity);
    return repo;
}

void destroy_repository(Repository *repo) {
    destroy_dynamic_array(repo->dyn_array);
    free(repo);
}

Product **get_repository_products(Repository *repo) {
    return (Product **) get_dynamic_array_elems(repo->dyn_array);
}

DynamicArray *get_repository_elems(Repository *repo) {
    return repo->dyn_array;
}

int get_product_index_in_repo(Repository *repo, char *name, int category) {
    Product **products = get_repository_products(repo);
    for (int i = 0; i < get_dynamic_array_size(repo->dyn_array); i++) {
        if (strcmp(get_product_name(products[i]), name) == 0 && get_product_category(products[i]) == category) {
            return i;
        }
    }
    return -1;
}

Product *get_product_on_position(Repository *repo, int position) {
    return get_repository_products(repo)[position];
}

Product *find_product_in_repo(Repository *repo, char *name, int category) {
    int product_index = get_product_index_in_repo(repo, name, category);
    if (product_index == -1) {
        return NULL;
    }
    return get_product_on_position(repo, product_index);
}

int get_repository_size(Repository *repo) {
    return get_dynamic_array_size(repo->dyn_array);
}

int add_product_to_repo(Repository *repo, Product *p) {
    int product_category = get_product_category(p);
    if (get_product_index_in_repo(repo, get_product_name(p), product_category) != -1) {
        return -1;
    }
    add_elem_to_dynamic_array(repo->dyn_array, p);
    return 0;
}

int remove_product_from_repo(Repository *repo, char *name, int category) {
    int product_index = get_product_index_in_repo(repo, name, category);
    if (product_index == -1) {
        return -1;
    }
    delete_elem_from_position(repo->dyn_array, product_index);
    return 0;
}

int update_product_in_repo(Repository *repo, Product *p) {
    int product_category = get_product_category(p);
    int product_index = get_product_index_in_repo(repo, get_product_name(p), product_category);
    if (product_index == -1) {
        return -1;
    }
    delete_elem_from_position(repo->dyn_array, product_index);
    insert_elem_to_position(repo->dyn_array, p, product_index);
    return 0;
}

DynamicArray *get_deep_copy_of_products(DynamicArray *da_products) {
    DynamicArray *copy_array = create_dynamic_array(get_dynamic_array_capacity(da_products));
    Product *current_product, *copy_product;
    char name[256];
    int category, day, month, year;
    double quantity;
    for (int i=0; i<get_dynamic_array_size(da_products); i++) {
        current_product = (Product*) get_elem_from_position(da_products, i);
        strcpy(name, get_product_name(current_product));
        category = get_product_category(current_product);
        quantity = get_product_quantity(current_product);
        day = get_product_expiration_day(current_product);
        month = get_product_expiration_month(current_product);
        year = get_product_expiration_year(current_product);
        copy_product = create_product(name, category, quantity, day, month, year);
        add_elem_to_dynamic_array(copy_array, copy_product);
    }
    return copy_array;
}

void change_elems(Repository *repo, DynamicArray *new_elems) {
    repo->dyn_array = new_elems;
}