//
// Created by VladB on 07-Mar-21.
//

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "test_service.h"
#include "../persistency/repository.h"
#include "../business/service.h"
#include "../utils/comparators_and_filters.h"

#define INITIAL_CAPACITY 2

void test_service_add() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);

    int response = srv_add_product(srv, "Sugar", 1, 2.7, 17, 5, 2001);
    assert(response == 0);
    assert(srv_get_no_products(srv) == 1);
    response = srv_add_product(srv, "Salt", 2, 4.9, 18, 5, 2001);
    assert(response == 0);
    assert(srv_get_no_products(srv) == 2);
    response = srv_add_product(srv, "Pepper", 3, 10.3, 19, 5, 2001);
    assert(response == 0);
    assert(srv_get_no_products(srv) == 3);
    // Just a side test to see if the dynamic array is still working correctly
    assert(get_dynamic_array_capacity(srv->repo->dyn_array) == 4);

    response = srv_add_product(srv, "Sugar", 1, 1.3, 17, 5, 2001);
    // Now srv_add_product should return 1, since it added to Sugar quantity
    assert(response == 1);
    assert(srv_get_no_products(srv) == 3);

    // See if the quantity of sugar was updated
    Product *sugar_product = find_product_in_repo(repo, "Sugar", 1);
    assert(fabs(get_product_quantity(sugar_product) - 4) < 0.0001);

    // If we add a new product, the expiration date of the updated product is the old date
    // This is an implementation choice, since it was not specified
    assert(get_product_expiration_day(sugar_product) == 17);
    assert(get_product_expiration_month(sugar_product) == 5);
    assert(get_product_expiration_year(sugar_product) == 2001);

    // We can also add a product with the same name, but in a different category
    // This makes logical sense in some cases and it doesn't in other cases. Again, this is an implementation
    // choice that I took since it was not specified.
    srv_add_product(srv, "Sugar", 2, 4.4, 20, 9, 2005);
    assert(srv_get_no_products(srv) == 4);

    // Also test that if we pass an invalid product, we get the expected output
    response = srv_add_product(srv, "", 15, -13.5, 83, 57, -2001);
    assert(response % 3 == 0);
    assert(response % 5 == 0);
    assert(response % 7 == 0);
    assert(response % 11 == 0);

    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
    destroy_undo_redo(srv->undo_redo);  // todo:
    destroy_repository(repo);
    destroy_service(srv);
}

void test_service_remove() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);

    srv_add_product(srv, "Sugar", 1, 2.7, 17, 5, 2001);
    assert(srv_get_no_products(srv) == 1);
    srv_add_product(srv, "Salt", 2, 4.9, 18, 5, 2001);
    assert(srv_get_no_products(srv) == 2);
    srv_add_product(srv, "Pepper", 3, 10.3, 19, 5, 2001);
    assert(srv_get_no_products(srv) == 3);
    srv_add_product(srv, "Sugar", 1, 1.3, 17, 5, 2001);
    assert(srv_get_no_products(srv) == 3);

    srv_remove_product(srv, "Pepper", 3);
    assert(srv_get_no_products(srv) == 2);
    assert(find_product_in_repo(srv->repo, "Pepper", 2) == NULL);
    assert(srv_remove_product(srv, "Chilli", 2) == -1);
    assert(srv_remove_product(srv, "Sugar", 2) == -1);

    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
    destroy_undo_redo(srv->undo_redo);
    destroy_repository(repo);
    destroy_service(srv);
}

void test_service_update() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);

    srv_add_product(srv, "Sugar", 1, 2.7, 17, 5, 2001);
    assert(srv_get_no_products(srv) == 1);
    srv_add_product(srv, "Salt", 2, 4.9, 18, 5, 2001);
    assert(srv_get_no_products(srv) == 2);
    srv_add_product(srv, "Sugar", 1, 1.3, 17, 5, 2001);
    assert(srv_get_no_products(srv) == 2);

    assert(srv_update_product(srv, "Sugar", 1, 10.9, 20, 6, 2010) == 0);
    DynamicArray *all_products = get_service_products(srv);


//    Product **all_products = get_all_products(srv);
    Product *p = (Product*) get_elem_from_position(all_products, 0);
    assert(fabs(get_product_quantity(p) - 10.9) < 0.0001);
    assert(get_product_expiration_day(p) == 20);
    assert(get_product_expiration_month(p) == 6);
    assert(get_product_expiration_year(p) == 2010);
    assert(srv_update_product(srv, "Salt", 3, 12.3, 20, 5, 2001) == -1);

    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
    destroy_undo_redo(srv->undo_redo);
    destroy_repository(repo);
    destroy_service(srv);
}

void test_filter_by_string() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);

    srv_add_product(srv, "Sugar", 1, 2.7, 17, 5, 2001);
    assert(srv_get_no_products(srv) == 1);
    srv_add_product(srv, "Salt", 2, 4.9, 18, 5, 2001);
    assert(srv_get_no_products(srv) == 2);
    srv_add_product(srv, "Pepper", 3, 5.13, 20, 9, 2011);
    assert(srv_get_no_products(srv) == 3);

    // Test the get products method in the service
    assert(get_service_products(srv) == get_repository_elems(repo));

    // "Sugar" and "Salt" have 'S' in them => They will be in the array
    DynamicArray *products_with_str = create_dynamic_array(INITIAL_CAPACITY);

    filter_by_name(get_repository_elems(repo), products_with_str, "S", string_filter);

    assert(get_dynamic_array_size(products_with_str) == 2);
    Product *p0 = (Product *) get_elem_from_position(products_with_str, 0);
    assert(strcmp(get_product_name(p0), "Sugar") == 0);
    p0 = (Product *) get_elem_from_position(products_with_str, 1);
    assert(strcmp(get_product_name(p0), "Salt") == 0);

    // No product has "abc" in its name => the dynamic array will be empty
    destroy_dynamic_array(products_with_str);
    products_with_str = create_dynamic_array(INITIAL_CAPACITY);

    filter_by_name(get_repository_elems(repo), products_with_str, "abc", string_filter);

    assert(get_dynamic_array_size(products_with_str) == 0);

    // If we give the emtpy string as argument => all products will be included
    destroy_dynamic_array(products_with_str);
    products_with_str = create_dynamic_array(INITIAL_CAPACITY);

    filter_by_name(get_repository_elems(repo), products_with_str, "", string_filter);

    assert(get_dynamic_array_size(products_with_str) == 3);

    // We test that the filter is case insensitive
    destroy_dynamic_array(products_with_str);
    products_with_str = create_dynamic_array(INITIAL_CAPACITY);

    filter_by_name(get_repository_elems(repo), products_with_str, "s", string_filter);

    // The result of this filter should be the same as the result of the filtering above,
    // where we filtered by "S"
    assert(get_dynamic_array_size(products_with_str) == 2);
    p0 = (Product *) get_elem_from_position(products_with_str, 0);
    assert(strcmp(get_product_name(p0), "Sugar") == 0);
    p0 = (Product *) get_elem_from_position(products_with_str, 1);
    assert(strcmp(get_product_name(p0), "Salt") == 0);

    destroy_dynamic_array(products_with_str);
    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
    destroy_undo_redo(srv->undo_redo);
    destroy_repository(srv->repo);
    destroy_service(srv);
}

void test_sort_products() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);

    srv_add_product(srv, "Sugar", 1, 4.9, 17, 5, 2001);
    assert(srv_get_no_products(srv) == 1);
    srv_add_product(srv, "Salt", 2, 2.7, 18, 5, 2001);
    assert(srv_get_no_products(srv) == 2);
    srv_add_product(srv, "Pepper", 3, 5.13, 20, 9, 2011);
    assert(srv_get_no_products(srv) == 3);
    srv_add_product(srv, "Chilli", 4, 10.4, 13, 7, 2013);
    assert(srv_get_no_products(srv) == 4);

    DynamicArray *da = repo->dyn_array;
    DynamicArray *copy = get_shallow_copy_of_dynamic_array(da);
    // sort ascending by quantity
    generic_sort_products(copy, ascending_quantity_comp);

    assert(get_product_category(get_elem_from_position(copy, 0)) == 2);
    assert(get_product_category(get_elem_from_position(copy, 1)) == 1);
    assert(get_product_category(get_elem_from_position(copy, 2)) == 3);
    assert(get_product_category(get_elem_from_position(copy, 3)) == 4);

    // Also test that just the copy was sorted, the original array is not modified
    assert(get_product_category(get_elem_from_position(da, 0)) == 1);
    assert(get_product_category(get_elem_from_position(da, 1)) == 2);
    assert(get_product_category(get_elem_from_position(da, 2)) == 3);
    assert(get_product_category(get_elem_from_position(da, 3)) == 4);

    // sort descending by name
    generic_sort_products(copy, descending_name_comp);
    assert(get_product_category(get_elem_from_position(copy, 0)) == 1);
    assert(get_product_category(get_elem_from_position(copy, 1)) == 2);
    assert(get_product_category(get_elem_from_position(copy, 2)) == 3);
    assert(get_product_category(get_elem_from_position(copy, 3)) == 4);

    // sort ascending by name
    generic_sort_products(copy, ascending_name_comp);
    assert(get_product_category(get_elem_from_position(copy, 0)) == 4);
    assert(get_product_category(get_elem_from_position(copy, 1)) == 3);
    assert(get_product_category(get_elem_from_position(copy, 2)) == 2);
    assert(get_product_category(get_elem_from_position(copy, 3)) == 1);

    // sort descending by expiration date (the products which expire further into the future will
    // be first in the array)
    generic_sort_products(copy, descending_expiration_comp);
    assert(get_product_category(get_elem_from_position(copy, 0)) == 4);
    assert(get_product_category(get_elem_from_position(copy, 1)) == 3);
    assert(get_product_category(get_elem_from_position(copy, 2)) == 2);
    assert(get_product_category(get_elem_from_position(copy, 3)) == 1);

    // sort ascending by expiration date (the products which expire sooner will be first in the array)
    generic_sort_products(copy, ascending_expiration_comp);
    assert(get_product_category(get_elem_from_position(copy, 0)) == 1);
    assert(get_product_category(get_elem_from_position(copy, 1)) == 2);
    assert(get_product_category(get_elem_from_position(copy, 2)) == 3);
    assert(get_product_category(get_elem_from_position(copy, 3)) == 4);

    destroy_dynamic_array(copy);
    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
destroy_undo_redo(srv->undo_redo);
    destroy_repository(repo);
    destroy_service(srv);
}

void test_filter_by_quantity() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);

    srv_add_product(srv, "Sugar", 1, 4.9, 17, 5, 2001);
    assert(srv_get_no_products(srv) == 1);
    srv_add_product(srv, "Salt", 2, 2.7, 18, 5, 2001);
    assert(srv_get_no_products(srv) == 2);
    srv_add_product(srv, "Pepper", 3, 5.13, 20, 9, 2011);
    assert(srv_get_no_products(srv) == 3);
    srv_add_product(srv, "Chilli", 4, 10.4, 13, 7, 2013);
    assert(srv_get_no_products(srv) == 4);
    srv_add_product(srv, "Apples", 1, 2.5, 20, 5, 2001);
    assert(srv_get_no_products(srv) == 5);
    srv_add_product(srv, "Pears", 2, 3.9, 25, 6, 2022);
    assert(srv_get_no_products(srv) == 6);

    DynamicArray *result = create_dynamic_array(INITIAL_CAPACITY);
    filter_by_quantity(get_repository_elems(repo), result, 5, greater_than_quantity_filter);
    assert(get_dynamic_array_size(result) == 2);
    destroy_dynamic_array(result);

    result = create_dynamic_array(INITIAL_CAPACITY);
    filter_by_quantity(get_repository_elems(repo), result, 4, less_than_quantity_filter);
    assert(get_dynamic_array_size(result) == 3);

    destroy_dynamic_array(result);
    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
    destroy_undo_redo(srv->undo_redo);
    destroy_repository(srv->repo);
    destroy_service(srv);
}

void test_filter_by_category() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);

    srv_add_product(srv, "Sugar", 1, 4.9, 17, 5, 2001);
    assert(srv_get_no_products(srv) == 1);
    srv_add_product(srv, "Salt", 2, 2.7, 18, 5, 2001);
    assert(srv_get_no_products(srv) == 2);
    srv_add_product(srv, "Pepper", 3, 5.13, 20, 9, 2011);
    assert(srv_get_no_products(srv) == 3);
    srv_add_product(srv, "Chilli", 4, 10.4, 13, 7, 2013);
    assert(srv_get_no_products(srv) == 4);
    srv_add_product(srv, "Apples", 1, 2.5, 20, 5, 2001);
    assert(srv_get_no_products(srv) == 5);
    srv_add_product(srv, "Pears", 2, 3.9, 25, 6, 2022);
    assert(srv_get_no_products(srv) == 6);

    DynamicArray *products_in_category = create_dynamic_array(INITIAL_CAPACITY);

    filter_by_category(get_repository_elems(repo), products_in_category, 1, category_filter);

    assert(get_dynamic_array_size(products_in_category) == 2);
    Product *p0 = (Product *) get_elem_from_position(products_in_category, 0);
    assert(strcmp(get_product_name(p0), "Sugar") == 0);
    p0 = (Product *) get_elem_from_position(products_in_category, 1);
    assert(strcmp(get_product_name(p0), "Apples") == 0);

    // If -1 is given as the category parameter, then all products are included
    destroy_dynamic_array(products_in_category);
    products_in_category = create_dynamic_array(INITIAL_CAPACITY);

    filter_by_category(get_repository_elems(repo), products_in_category, -1, category_filter);

    assert(get_dynamic_array_size(products_in_category) == 6);
    p0 = (Product *) get_elem_from_position(products_in_category, 0);
    assert(strcmp(get_product_name(p0), "Sugar") == 0);
    p0 = (Product *) get_elem_from_position(products_in_category, 5);
    assert(strcmp(get_product_name(p0), "Pears") == 0);

    destroy_dynamic_array(products_in_category);
    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
    destroy_undo_redo(srv->undo_redo);
    destroy_repository(srv->repo);
    destroy_service(srv);
}

void test_keep_close_expiration_products() {
    DynamicArray *da = create_dynamic_array(INITIAL_CAPACITY);
    DynamicArray *soon_to_expire = create_dynamic_array(INITIAL_CAPACITY);
    time_t t = time(NULL);
    struct tm current_date = *localtime(&t);
    int current_day = current_date.tm_mday;
    int current_month = current_date.tm_mon + 1;
    int current_year = current_date.tm_year + 1900;
    Product *p0 = create_product("Sugar", 1, 2.5, current_day + 1, current_month, current_year);
    Product *p1 = create_product("Salt", 2, 3.14, current_day, current_month + 1, current_year);
    Product *p2 = create_product("Pepper", 3, 5.31, current_day, current_month, current_year + 1);
    add_elem_to_dynamic_array(da, p0);
    add_elem_to_dynamic_array(da, p1);
    add_elem_to_dynamic_array(da, p2);

    filter_by_expiration(da, soon_to_expire, 1, expiration_date_filter);

    assert(get_dynamic_array_size(soon_to_expire) == 1);
    assert(get_elem_from_position(soon_to_expire, 0) == p0);

    destroy_dynamic_array(soon_to_expire);
    soon_to_expire = create_dynamic_array(INITIAL_CAPACITY);

    filter_by_expiration(da, soon_to_expire, 35, expiration_date_filter);

    assert(get_dynamic_array_size(soon_to_expire) == 2);
    assert(get_elem_from_position(soon_to_expire, 0) == p0);
    assert(get_elem_from_position(soon_to_expire, 1) == p1);

    destroy_dynamic_array(soon_to_expire);
    soon_to_expire = create_dynamic_array(INITIAL_CAPACITY);

    filter_by_expiration(da, soon_to_expire, 367, expiration_date_filter);

    assert(get_dynamic_array_size(soon_to_expire) == 3);
    assert(get_elem_from_position(soon_to_expire, 0) == p0);
    assert(get_elem_from_position(soon_to_expire, 1) == p1);
    assert(get_elem_from_position(soon_to_expire, 2) == p2);

    destroy_dynamic_array(soon_to_expire);
    destroy_product(p0);
    destroy_product(p1);
    destroy_product(p2);
    destroy_dynamic_array(da);
}

void test_service_undo_add() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);
    assert(srv_get_no_products(srv) == 0);
    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);

    srv_add_product(srv, "Chilli", 3, 8.14, 27, 3, 2022);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
    assert(srv_get_no_products(srv) == 1);
//    srv_add_product(srv, "Chilli", 3, 8.14, 27, 3, 2022);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    apply_undo(srv);
    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 1);
    assert(srv_get_no_products(srv) == 0);
//    apply_undo(srv);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 1);
//    assert(srv_get_no_products(srv) == 0);

    srv_add_product(srv, "Sugar", 1, 4.9, 17, 5, 2001);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//
//    srv_add_product(srv, "Sugar", 1, 4.9, 17, 5, 2001);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_add_product(srv, "Pepper", 1, 5.14, 30, 7, 2021);
    assert(srv_get_no_products(srv) == 2);
    assert(get_undo_stack_length(srv->undo_redo) == 2);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_add_product(srv, "Pepper", 1, 5.14, 30, 7, 2021);
//    assert(srv_get_no_products(srv) == 2);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 2);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    apply_undo(srv);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 1);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 1);
//
    assert(apply_undo(srv) == 0);
    assert(srv_get_no_products(srv) == 0);
    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 2);
//    assert(apply_undo(srv) == 0);
//    assert(srv_get_no_products(srv) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 2);
//
    assert(apply_undo(srv) == 1);
    assert(srv_get_no_products(srv) == 0);
    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 2);
//    assert(apply_undo(srv) == 1);
//    assert(srv_get_no_products(srv) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 2);
//
    srv_add_product(srv, "Chilli", 3, 8.14, 27, 3, 2022);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_add_product(srv, "Chilli", 3, 8.14, 27, 3, 2022);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    apply_undo(srv);
    assert(srv_get_no_products(srv) == 0);
    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 1);
//    apply_undo(srv);
//    assert(srv_get_no_products(srv) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 1);
//
    free_all_products(get_repository_elems(repo));
    destroy_undo_redo(srv->undo_redo);
    destroy_repository(repo);
    destroy_service(srv);
//    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
//    destroy_repository(repo);
//    destroy_service(srv);
}

void test_service_undo_remove() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);
    assert(srv_get_no_products(srv) == 0);
    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 0);

//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_add_product(srv, "Chilli", 3, 8.14, 27, 3, 2022);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_add_product(srv, "Chilli", 3, 8.14, 27, 3, 2022);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_remove_product(srv, "Chilli", 3);
    assert(srv_get_no_products(srv) == 0);
    assert(get_undo_stack_length(srv->undo_redo) == 2);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_remove_product(srv, "Chilli", 3);
//    assert(srv_get_no_products(srv) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 2);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    apply_undo(srv);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 1);
//    apply_undo(srv);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 1);
//
    apply_undo(srv);
    assert(srv_get_no_products(srv) == 0);
    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 2);
//    apply_undo(srv);
//    assert(srv_get_no_products(srv) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 2);
//
    free_all_products(get_repository_elems(repo));
    destroy_undo_redo(srv->undo_redo);
    destroy_repository(repo);
    destroy_service(srv);
//    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
//    destroy_repository(repo);
//    destroy_service(srv);
}

void test_service_undo_update() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);
    assert(srv_get_no_products(srv) == 0);

    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_add_product(srv, "Chilli", 3, 8.14, 27, 3, 2022);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_add_product(srv, "Chilli", 3, 8.14, 27, 3, 2022);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_update_product(srv, "Chilli", 3, 10.5, 28, 4, 2023);
    assert(srv_get_no_products(srv) == 1);
    Product *p = find_product_in_repo(repo, "Chilli", 3);
    assert(get_product_expiration_day(p) == 28);
    assert(get_undo_stack_length(srv->undo_redo) == 2);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_update_product(srv, "Chilli", 3, 10.5, 28, 4, 2023);
//    assert(srv_get_no_products(srv) == 1);
//    // Test that the update took place
//    Product *p = find_product_in_repo(repo, "Chilli", 3);
//    assert(get_product_expiration_day(p) == 28);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 2);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    apply_undo(srv);
    assert(srv_get_no_products(srv) == 1);
    p = find_product_in_repo(repo, "Chilli", 3);
    assert(get_product_expiration_day(p) == 27);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 1);

//    apply_undo(srv);
//    assert(get_undo_stack_length(srv->undo_redo) == 0);
//    assert(get_redo_stack_length(srv->undo_redo) == 2);


//    apply_undo(srv);
//    assert(srv_get_no_products(srv) == 1);
//    p = find_product_in_repo(repo, "Chilli", 3);
//    assert(get_product_expiration_day(p) == 27);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 1);
//
    free_all_products(get_repository_elems(repo));



    destroy_undo_redo(srv->undo_redo);



    destroy_repository(repo);
    destroy_service(srv);
//    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
//    destroy_repository(repo);
//    destroy_service(srv);
}

void test_service_redo_add_simple() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);
    assert(srv_get_no_products(srv) == 0);
    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_add_product(srv, "Chilli", 3, 8.14, 27, 3, 2022);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_add_product(srv, "Chilli", 3, 8.14, 27, 3, 2022);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    apply_undo(srv);
    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 1);
    assert(srv_get_no_products(srv) == 0);
//    apply_undo(srv);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 1);
//    assert(srv_get_no_products(srv) == 0);
//
    apply_redo(srv);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
    assert(srv_get_no_products(srv) == 1);
//    apply_redo(srv);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//    assert(srv_get_no_products(srv) == 1);
//
    free_all_products(get_repository_elems(repo));
    destroy_undo_redo(srv->undo_redo);
    destroy_repository(repo);
    destroy_service(srv);
//    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
//    destroy_repository(repo);
//    destroy_service(srv);
}

void test_service_redo_add_complex() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);
    assert(srv_get_no_products(srv) == 0);

    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_add_product(srv, "Sugar", 1, 4.9, 17, 5, 2001);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_add_product(srv, "Sugar", 1, 4.9, 17, 5, 2001);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_add_product(srv, "Pepper", 1, 5.14, 30, 7, 2021);
    assert(srv_get_no_products(srv) == 2);
    assert(get_undo_stack_length(srv->undo_redo) == 2);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_add_product(srv, "Pepper", 1, 5.14, 30, 7, 2021);
//    assert(srv_get_no_products(srv) == 2);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 2);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    apply_undo(srv);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 1);
//    apply_undo(srv);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 1);
//
    apply_undo(srv);
    assert(srv_get_no_products(srv) == 0);
    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 2);
//    apply_undo(srv);
//    assert(srv_get_no_products(srv) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 2);
//
    apply_redo(srv);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 1);
//    apply_redo(srv);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 1);
//
    apply_redo(srv);
    assert(srv_get_no_products(srv) == 2);
    assert(get_undo_stack_length(srv->undo_redo) == 2);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    apply_redo(srv);
//    assert(srv_get_no_products(srv) == 2);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 2);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    apply_undo(srv);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 1);
//    apply_undo(srv);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 1);
//
    apply_undo(srv);
    assert(srv_get_no_products(srv) == 0);
    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 2);
//    apply_undo(srv);
//    assert(srv_get_no_products(srv) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 2);
//
    srv_add_product(srv, "Chilli", 2, 13.14, 4, 3, 2023);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_add_product(srv, "Chilli", 2, 13.14, 4, 3, 2023);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    assert(apply_redo(srv) == 1);
//    assert(apply_redo(srv) == 1);
//
    free_all_products(get_repository_elems(repo));
    destroy_undo_redo(srv->undo_redo);
    destroy_repository(repo);
    destroy_service(srv);
//    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
//    destroy_repository(repo);
//    destroy_service(srv);
}

void test_service_redo_remove() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);
    assert(srv_get_no_products(srv) == 0);

    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_add_product(srv, "Sugar", 1, 4.9, 17, 5, 2001);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_add_product(srv, "Sugar", 1, 4.9, 17, 5, 2001);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_add_product(srv, "Pepper", 1, 5.14, 30, 7, 2021);
    assert(srv_get_no_products(srv) == 2);
    assert(get_undo_stack_length(srv->undo_redo) == 2);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_add_product(srv, "Pepper", 1, 5.14, 30, 7, 2021);
//    assert(srv_get_no_products(srv) == 2);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 2);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_remove_product(srv, "Sugar", 1);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 3);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_remove_product(srv, "Sugar", 1);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 3);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    apply_undo(srv);
    assert(srv_get_no_products(srv) == 2);
    assert(get_undo_stack_length(srv->undo_redo) == 2);
    assert(get_redo_stack_length(srv->undo_redo) == 1);
//    apply_undo(srv);
//    assert(srv_get_no_products(srv) == 2);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 2);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 1);
//
    apply_redo(srv);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 3);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    apply_redo(srv);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 3);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    free_all_products(get_repository_elems(repo));
    destroy_undo_redo(srv->undo_redo);
    destroy_repository(repo);
    destroy_service(srv);
//    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
//    destroy_repository(repo);
//    destroy_service(srv);
}

void test_service_redo_update() {
    Repository *repo = create_repository(INITIAL_CAPACITY);
    Service *srv = create_service(repo);
    assert(srv_get_no_products(srv) == 0);

    assert(get_undo_stack_length(srv->undo_redo) == 0);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 0);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_add_product(srv, "Sugar", 1, 4.9, 17, 5, 2001);
    assert(srv_get_no_products(srv) == 1);
    assert(get_undo_stack_length(srv->undo_redo) == 1);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_add_product(srv, "Sugar", 1, 4.9, 17, 5, 2001);
//    assert(srv_get_no_products(srv) == 1);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 1);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_add_product(srv, "Pepper", 1, 5.14, 30, 7, 2021);
    assert(srv_get_no_products(srv) == 2);
    assert(get_undo_stack_length(srv->undo_redo) == 2);
    assert(get_redo_stack_length(srv->undo_redo) == 0);
//    srv_add_product(srv, "Pepper", 1, 5.14, 30, 7, 2021);
//    assert(srv_get_no_products(srv) == 2);
//    assert(get_dynamic_array_size(srv->states_for_undo) == 2);
//    assert(get_dynamic_array_size(srv->states_for_redo) == 0);
//
    srv_update_product(srv, "Pepper", 1, 13.29, 15, 8, 2023);
    assert(srv_get_no_products(srv) == 2);
    Product *p = find_product_in_repo(repo, "Pepper", 1);
    assert(get_product_expiration_day(p) == 15);
//    srv_update_product(srv, "Pepper", 1, 13.29, 15, 8, 2023);
//    assert(srv_get_no_products(srv) == 2);
//    Product *p = find_product_in_repo(repo, "Pepper", 1);
//    assert(get_product_expiration_day(p) == 15);
//
    apply_undo(srv);
    assert(srv_get_no_products(srv) == 2);
    p = find_product_in_repo(repo, "Pepper", 1);
    assert(get_product_expiration_day(p) == 30);
//    apply_undo(srv);
//    assert(srv_get_no_products(srv) == 2);
//    p = find_product_in_repo(repo, "Pepper", 1);
//    assert(get_product_expiration_day(p) == 30);
//
    apply_redo(srv);
    assert(srv_get_no_products(srv) == 2);
    p = find_product_in_repo(repo, "Pepper", 1);
    assert(get_product_expiration_day(p) == 15);
//    apply_redo(srv);
//    assert(srv_get_no_products(srv) == 2);
//    p = find_product_in_repo(repo, "Pepper", 1);
//    assert(get_product_expiration_day(p) == 15);
//
    free_all_products(get_repository_elems(repo));
    destroy_undo_redo(srv->undo_redo);
    destroy_repository(repo);
    destroy_service(srv);
//    free_all_products(get_repository_elems(repo));
//    clear_history_states(srv->states_for_redo);
//    clear_history_states(srv->states_for_undo);
//    destroy_repository(repo);
//    destroy_service(srv);
}

void run_all_service_tests() {
    printf("Starting service tests...\n");
    test_service_add();
    test_service_remove();
    test_service_update();
    test_filter_by_string();
    test_sort_products();
    test_filter_by_category();
    test_filter_by_quantity();
    test_keep_close_expiration_products();
    test_service_undo_add();
    test_service_undo_remove();
    test_service_undo_update();
    test_service_redo_add_simple();
    test_service_redo_add_complex();
    test_service_redo_remove();
    test_service_redo_update();
    printf("Service tests done.\n");
}