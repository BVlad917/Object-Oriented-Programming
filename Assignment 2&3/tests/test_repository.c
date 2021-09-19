//
// Created by VladB on 07-Mar-21.
//

#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "test_repository.h"
#include "../persistency/repository.h"

#define INIT_CAPACITY 2

void test_add_to_repo() {
    Repository* repo = create_repository(INIT_CAPACITY);
    Product* p0 = create_product("Sugar", 1, 2.5, 17, 5, 2001);
    add_product_to_repo(repo, p0);
    assert(get_repository_size(repo) == 1);
    Product* p1 = create_product("Salt", 2, 3.7, 18, 5, 2001);
    add_product_to_repo(repo, p1);
    assert(get_repository_size(repo) == 2);
    Product* p2 = create_product("Pepper", 3, 4.9, 19, 5, 2001);
    add_product_to_repo(repo, p2);
    assert(get_repository_size(repo) == 3);

    assert(find_product_in_repo(repo, "Sugar", 1) == p0);
    assert(find_product_in_repo(repo, "Pepper", 3) == p2);
    assert(find_product_in_repo(repo, "Chilli", 1) == NULL);

    Product** products = get_repository_products(repo);
    assert(products[0] == p0);
    assert(products[1] == p1);
    assert(products[2] == p2);

    // Test that if we try to add a product with the same name & category => doesn't work
    Product* p3 = create_product("Sugar", 1, 17.5, 30, 5, 2020);
    int added = add_product_to_repo(repo, p3);
    assert(added < 0);
    assert(get_repository_size(repo) == 3);

    destroy_product(p0);
    destroy_product(p1);
    destroy_product(p2);
    destroy_product(p3);
    destroy_repository(repo);
}

void test_remove_from_repo() {
    Repository* repo = create_repository(INIT_CAPACITY);
    Product* p0 = create_product("Sugar", 1, 2.5, 17, 5, 2001);
    add_product_to_repo(repo, p0);
    assert(get_repository_size(repo) == 1);
    Product* p1 = create_product("Salt", 2, 3.7, 18, 5, 2001);
    add_product_to_repo(repo, p1);
    assert(get_repository_size(repo) == 2);
    Product* p2 = create_product("Pepper", 3, 4.9, 19, 5, 2001);
    add_product_to_repo(repo, p2);
    assert(get_repository_size(repo) == 3);

    remove_product_from_repo(repo, "Sugar", 1);
    assert(get_repository_size(repo) == 2);
    assert(get_elem_from_position(get_repository_elems(repo), 0) == p1);
    assert(get_elem_from_position(get_repository_elems(repo), 1) == p2);
    int removed = remove_product_from_repo(repo, "Salt", 3);
    assert(removed < 0);
    assert(get_repository_size(repo) == 2);

    assert(get_elem_from_position(get_repository_elems(repo), 0) == p1);
    assert(get_elem_from_position(get_repository_elems(repo), 1) == p2);

    destroy_product(p0);
    destroy_product(p1);
    destroy_product(p2);
    destroy_repository(repo);
}

void test_update_repo() {
    Repository* repo = create_repository(INIT_CAPACITY);
    Product* p0 = create_product("Sugar", 1, 2.5, 17, 5, 2001);
    add_product_to_repo(repo, p0);
    assert(get_repository_size(repo) == 1);
    Product* p1 = create_product("Salt", 2, 3.7, 18, 5, 2001);
    add_product_to_repo(repo, p1);
    assert(get_repository_size(repo) == 2);
    Product* p2 = create_product("Pepper", 3, 4.9, 19, 5, 2001);
    add_product_to_repo(repo, p2);
    assert(get_repository_size(repo) == 3);

    Product* p0_new = create_product("Sugar", 1, 10.5, 1, 6, 2002);
    assert(update_product_in_repo(repo, p0_new) == 0);
    assert(get_elem_from_position(get_repository_elems(repo), 0) == p0_new);
    double new_quantity = get_product_quantity(get_elem_from_position(repo->dyn_array, 0));
    assert(fabs(new_quantity - p0_new->quantity) < 0.00001);

    Product* invalid_update_p = create_product("Salt", 3, 10.9, 25, 4, 2002);
    assert(update_product_in_repo(repo, invalid_update_p) == -1);
    assert(get_elem_from_position(get_repository_elems(repo), 1) == p1);
    assert(get_elem_from_position(get_repository_elems(repo), 1) != invalid_update_p);

    destroy_product(invalid_update_p);
    destroy_product(p0_new);
    destroy_product(p0);
    destroy_product(p1);
    destroy_product(p2);
    destroy_repository(repo);
}

void test_deep_copy_products() {
    Repository* repo = create_repository(INIT_CAPACITY);
    Product* p0 = create_product("Sugar", 1, 2.5, 17, 5, 2001);
    add_product_to_repo(repo, p0);
    assert(get_repository_size(repo) == 1);
    Product* p1 = create_product("Salt", 2, 3.7, 18, 5, 2001);
    add_product_to_repo(repo, p1);
    assert(get_repository_size(repo) == 2);
    Product* p2 = create_product("Pepper", 3, 4.9, 19, 5, 2001);
    add_product_to_repo(repo, p2);
    assert(get_repository_size(repo) == 3);

    DynamicArray *da = get_deep_copy_of_products(get_repository_elems(repo));
    Product *p0_copy = get_elem_from_position(da, 0);
    Product *p1_copy = get_elem_from_position(da, 1);
    Product *p2_copy = get_elem_from_position(da, 2);

    assert(p0 != p0_copy);
    assert(p1 != p1_copy);
    assert(p2 != p2_copy);
    assert(get_product_name(p0) != get_product_name(p0_copy));

    assert(strcmp(get_product_name(p0), get_product_name(p0_copy)) == 0);
    assert(get_product_category(p1) == get_product_category(p1_copy));
    assert(fabs(get_product_quantity(p2) - get_product_quantity(p2_copy)) == 0);
    assert(get_product_expiration_year(p1) == get_product_expiration_year(p1_copy));

    destroy_product(p0_copy);
    destroy_product(p1_copy);
    destroy_product(p2_copy);
    destroy_dynamic_array(da);
    destroy_product(p0);
    destroy_product(p1);
    destroy_product(p2);
    destroy_repository(repo);
}

void test_change_elems() {
    Repository* repo = create_repository(INIT_CAPACITY);
    Product* p0 = create_product("Sugar", 1, 2.5, 17, 5, 2001);
    add_product_to_repo(repo, p0);
    assert(get_repository_size(repo) == 1);
    Product *p1 = create_product("Salt", 2, 3.7, 18, 5, 2001);
    add_product_to_repo(repo, p1);
    assert(get_repository_size(repo) == 2);
    Product *p2 = create_product("Pepper", 3, 4.9, 19, 5, 2001);
    add_product_to_repo(repo, p2);
    assert(get_repository_size(repo) == 3);

    DynamicArray *new_elems = create_dynamic_array(INIT_CAPACITY);
    Product *p3 = create_product("Apples", 4, 2.5, 20, 7, 2021);
    add_elem_to_dynamic_array(new_elems, p3);
    Product *p4 = create_product("Pears", 4, 10.35, 21, 8, 2022);
    add_elem_to_dynamic_array(new_elems, p4);
    assert(get_dynamic_array_size(new_elems) == 2);

    DynamicArray *old_elems = get_repository_elems(repo);
    change_elems(repo, new_elems);
    assert(get_repository_size(repo) == 2);
    assert(get_repository_products(repo)[1] == p4);
    assert(get_dynamic_array_size(old_elems) == 3);

    destroy_product(p4);
    destroy_product(p3);
    destroy_repository(repo);
    destroy_product(p0);
    destroy_product(p1);
    destroy_product(p2);
    destroy_dynamic_array(old_elems);
}

void run_all_repo_tests() {
    printf("Starting repository tests...\n");
    test_add_to_repo();
    test_remove_from_repo();
    test_update_repo();
    test_deep_copy_products();
    test_change_elems();
    printf("Repository tests done.\n");
}