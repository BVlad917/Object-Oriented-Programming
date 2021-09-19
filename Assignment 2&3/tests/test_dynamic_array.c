//
// Created by VladB on 07-Mar-21.
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "test_dynamic_array.h"
#include "../dynamic_array/dynamic_array.h"
#include "../domain/product.h"

#define INIT_CAPACITY 2

void test_dynamic_array_add_and_remove() {
    DynamicArray *da = create_dynamic_array(INIT_CAPACITY);
    assert(get_dynamic_array_size(da) == 0);
    assert(get_dynamic_array_capacity(da) == INIT_CAPACITY);
    Product *p = create_product("Sugar", 0, 2.5, 17, 5, 2001);
    add_elem_to_dynamic_array(da, p);
    assert(get_dynamic_array_size(da) == 1);
    Product *p2 = create_product("Salt", 0, 3.31, 18, 5, 2001);
    add_elem_to_dynamic_array(da, p2);
    assert(get_dynamic_array_size(da) == 2);
    assert(get_dynamic_array_size(da) == get_dynamic_array_capacity(da));
    Product *p3 = create_product("Pepper", 2, 4.41, 19, 5, 2001);
    add_elem_to_dynamic_array(da, p3);
    assert(get_dynamic_array_size(da) == 3);
    assert(get_dynamic_array_capacity(da) == 4);

    Product **elems = (Product **) get_dynamic_array_elems(da);
    assert(strcmp(get_product_name(elems[0]), "Sugar") == 0);
    assert(fabs(get_product_quantity(elems[1]) - 3.31) < 0.0001);
    assert(get_product_category(elems[2]) == 2);

    delete_elem_from_position(da, 2);
    assert(get_dynamic_array_size(da) == 2);
    assert(strcmp(get_product_name(elems[0]), "Sugar") == 0);
    assert(fabs(get_product_quantity(elems[1]) - 3.31) < 0.0001);

    // Now, the destroy part
    // First we destroy the elements from the array. THEN, we destroy the array itself.
    destroy_product(p);
    destroy_product(p2);
    destroy_product(p3);
    destroy_dynamic_array(da);
}

void test_dynamic_array_insert_to_position() {
    DynamicArray *da = create_dynamic_array(INIT_CAPACITY);
    assert(get_dynamic_array_size(da) == 0);
    assert(get_dynamic_array_capacity(da) == INIT_CAPACITY);
    Product *p = create_product("Sugar", 0, 2.5, 17, 5, 2001);
    add_elem_to_dynamic_array(da, p);
    assert(get_dynamic_array_size(da) == 1);
    Product *p2 = create_product("Salt", 0, 3.31, 18, 5, 2001);
    add_elem_to_dynamic_array(da, p2);
    assert(get_dynamic_array_size(da) == 2);
    assert(get_dynamic_array_size(da) == get_dynamic_array_capacity(da));
    Product *p3 = create_product("Pepper", 2, 4.41, 19, 5, 2001);
    add_elem_to_dynamic_array(da, p3);
    assert(get_dynamic_array_size(da) == 3);
    assert(get_dynamic_array_capacity(da) == 4);

    // Just want to test if <get_elem_from_position()> works here, before using it for the below test
    assert((Product*)get_elem_from_position(da, 2) == p3);

    Product *p4 = create_product("Chilli", 3, 5.5, 20, 5, 2001);
    insert_elem_to_position(da, p4, 1);
    assert(get_dynamic_array_size(da) == 4);
    assert((Product*)get_elem_from_position(da, 1) == p4);
    assert((Product*)get_elem_from_position(da, 2) == p2);
    assert((Product*)get_elem_from_position(da, 3) == p3);
    assert((Product*)get_elem_from_position(da, 0) == p);
    destroy_product(p);
    destroy_product(p2);
    destroy_product(p3);
    destroy_product(p4);
    destroy_dynamic_array(da);
}

void test_dynamic_array_shallow_copy() {
    DynamicArray *da = create_dynamic_array(INIT_CAPACITY);
    Product *p = create_product("Sugar", 0, 2.5, 17, 5, 2001);
    add_elem_to_dynamic_array(da, p);
    assert(get_dynamic_array_size(da) == 1);
    Product *p2 = create_product("Salt", 0, 3.31, 18, 5, 2001);
    add_elem_to_dynamic_array(da, p2);
    assert(get_dynamic_array_size(da) == 2);

    DynamicArray *copy_array = get_shallow_copy_of_dynamic_array(da);
    Product **originals = (Product **) get_dynamic_array_elems(da);
    Product **copied = (Product **) get_dynamic_array_elems(copy_array);

    for (int i=0; i<get_dynamic_array_size(copy_array); i++) {
        assert(get_product_category(originals[i]) == get_product_category(copied[i]));
        assert(get_product_expiration_day(originals[i]) == get_product_expiration_day(copied[i]));
        assert(get_product_expiration_month(originals[i]) == get_product_expiration_month(copied[i]));
        assert(get_product_expiration_year(originals[i]) == get_product_expiration_year(copied[i]));
    }

    destroy_product(p);
    destroy_product(p2);
    destroy_dynamic_array(da);
    destroy_dynamic_array(copy_array);
}

void run_all_dynamic_array_tests() {
    printf("Starting dynamic array tests...\n");
    test_dynamic_array_add_and_remove();
    test_dynamic_array_insert_to_position();
    test_dynamic_array_shallow_copy();
    printf("Dynamic array tests done.\n");
}