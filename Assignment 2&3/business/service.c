//
// Created by VladB on 07-Mar-21.
//

#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "service.h"
#include "../validation/product_validator.h"
#include "../validation/category_validator.h"

#define STATES_HISTORY_INITIAL_SIZE 4

Service *create_service(Repository *repo) {
    Service *srv = (Service *) malloc(sizeof(Service));
    srv->repo = repo;
    srv->undo_redo = create_undo_redo();
//    srv->states_for_undo = create_dynamic_array(STATES_HISTORY_INITIAL_SIZE);
//    srv->states_for_redo = create_dynamic_array(STATES_HISTORY_INITIAL_SIZE);
    return srv;
}

void destroy_service(Service *srv) {
//    destroy_dynamic_array(srv->states_for_undo);
//    destroy_dynamic_array(srv->states_for_redo);
    free(srv);
}

//void save_current_state_as_undo(Service *srv) {
//    DynamicArray *current_state = get_deep_copy_of_products(get_repository_elems(srv->repo));
//    add_elem_to_dynamic_array(srv->states_for_undo, current_state);
//}

//void save_current_state_as_redo(Service *srv) {
//    DynamicArray *current_state = get_deep_copy_of_products(get_repository_elems(srv->repo));
//    add_elem_to_dynamic_array(srv->states_for_redo, current_state);
//}

//void clear_history_states(DynamicArray *history_states) {
//    DynamicArray *current_state;
//    for (int i = 0; i < get_dynamic_array_size(history_states); i++) {
//        current_state = (DynamicArray *) get_elem_from_position(history_states, i);
//        free_all_products(current_state);
//        destroy_dynamic_array(current_state);
//    }
//    while (get_dynamic_array_size(history_states)) {
//        delete_elem_from_position(history_states, get_dynamic_array_size(history_states) - 1);
//    }
//}

//int apply_undo(Service *srv) {
//    if (get_dynamic_array_size(srv->states_for_undo) == 0) {
//        return 1;
//    }
//    int nr_undo_states = get_dynamic_array_size(srv->states_for_undo);
//    DynamicArray *prev_state = (DynamicArray *) get_elem_from_position(srv->states_for_undo, nr_undo_states - 1);
//    delete_elem_from_position(srv->states_for_undo, nr_undo_states - 1);
//
//    save_current_state_as_redo(srv);
//    free_all_products(get_repository_elems(srv->repo));
//    destroy_dynamic_array(get_repository_elems(srv->repo));
//    change_elems(srv->repo, prev_state);
//    return 0;
//}
//
//int apply_redo(Service *srv) {
//    if (get_dynamic_array_size(srv->states_for_redo) == 0) {
//        return 1;
//    }
//    int nr_redo_states = get_dynamic_array_size(srv->states_for_redo);
//    DynamicArray *prev_state = (DynamicArray *) get_elem_from_position(srv->states_for_redo, nr_redo_states - 1);
//    delete_elem_from_position(srv->states_for_redo, nr_redo_states - 1);
//
//    save_current_state_as_undo(srv);
//    free_all_products(get_repository_elems(srv->repo));
//    destroy_dynamic_array(get_repository_elems(srv->repo));
//    change_elems(srv->repo, prev_state);
//    return 0;
//}

int apply_undo(Service *srv) {
    if (get_undo_stack_length(srv->undo_redo) == 0) {
        return 1;
    }
    Operation *last_op = get_last_undo(srv->undo_redo);
    if (strcmp(get_op_type(last_op), "add") == 0) {
        redo_add(srv->undo_redo, get_op_product(last_op));
        Product *copy = create_product(get_product_name(get_op_product(last_op)),
                                       get_product_category(get_op_product(last_op)),
                                       get_product_quantity(get_op_product(last_op)),
                                       get_product_expiration_day(get_op_product(last_op)),
                                       get_product_expiration_month(get_op_product(last_op)),
                                       get_product_expiration_year(get_op_product(last_op)));
        add_product_to_repo(srv->repo, copy);
        destroy_op(last_op);
        delete_elem_from_position(get_undo_list(srv->undo_redo), get_dynamic_array_size(get_undo_list(srv->undo_redo)) - 1);

    } else if (strcmp(get_op_type(last_op), "delete") == 0) {
        redo_remove(srv->undo_redo, get_op_product(last_op));
        Product *repo_prod = find_product_in_repo(srv->repo, get_product_name(get_op_product(last_op)),
                                                  get_product_category(get_op_product(last_op)));
        remove_product_from_repo(srv->repo, get_product_name(get_op_product(last_op)),
                                 get_product_category(get_op_product(last_op)));
        destroy_product(repo_prod);
        destroy_op(last_op);
        delete_elem_from_position(get_undo_list(srv->undo_redo), get_dynamic_array_size(get_undo_list(srv->undo_redo)) - 1);

    } else if (strcmp(get_op_type(last_op), "update") == 0) {
        Product *old = find_product_in_repo(srv->repo, get_product_name(get_op_product(last_op)),
                                            get_product_category(get_op_product(last_op)));
        redo_update(srv->undo_redo, old);
        Product *copy = create_product(get_product_name(get_op_product(last_op)),
                                       get_product_category(get_op_product(last_op)),
                                       get_product_quantity(get_op_product(last_op)),
                                       get_product_expiration_day(get_op_product(last_op)),
                                       get_product_expiration_month(get_op_product(last_op)),
                                       get_product_expiration_year(get_op_product(last_op)));
        update_product_in_repo(srv->repo, copy);
        destroy_product(old);
        destroy_op(last_op);
        delete_elem_from_position(get_undo_list(srv->undo_redo), get_dynamic_array_size(get_undo_list(srv->undo_redo)) - 1);
    }
    return 0;
}

int apply_redo(Service *srv) {
    if (get_redo_stack_length(srv->undo_redo) == 0) {
        return 1;
    }
    Operation *last_op = get_last_redo(srv->undo_redo);
    if (strcmp(get_op_type(last_op), "add") == 0) {
        undo_add(srv->undo_redo, get_op_product(last_op));
        Product *copy = create_product(get_product_name(get_op_product(last_op)),
                                       get_product_category(get_op_product(last_op)),
                                       get_product_quantity(get_op_product(last_op)),
                                       get_product_expiration_day(get_op_product(last_op)),
                                       get_product_expiration_month(get_op_product(last_op)),
                                       get_product_expiration_year(get_op_product(last_op)));
        add_product_to_repo(srv->repo, copy);
        destroy_op(last_op);
        delete_elem_from_position(get_redo_list(srv->undo_redo), get_dynamic_array_size(get_redo_list(srv->undo_redo)) - 1);
    } else if (strcmp(get_op_type(last_op), "delete") == 0) {
        undo_remove(srv->undo_redo, get_op_product(last_op));
        Product *repo_prod = find_product_in_repo(srv->repo, get_product_name(get_op_product(last_op)),
                                                  get_product_category(get_op_product(last_op)));
        remove_product_from_repo(srv->repo, get_product_name(get_op_product(last_op)),
                                 get_product_category(get_op_product(last_op)));
        destroy_product(repo_prod);
        destroy_op(last_op);
        delete_elem_from_position(get_redo_list(srv->undo_redo), get_dynamic_array_size(get_redo_list(srv->undo_redo)) - 1);
    } else if (strcmp(get_op_type(last_op), "update") == 0) {
        Product *old = find_product_in_repo(srv->repo, get_product_name(get_op_product(last_op)),
                                            get_product_category(get_op_product(last_op)));
        undo_update(srv->undo_redo, old);
        Product *copy = create_product(get_product_name(get_op_product(last_op)),
                                       get_product_category(get_op_product(last_op)),
                                       get_product_quantity(get_op_product(last_op)),
                                       get_product_expiration_day(get_op_product(last_op)),
                                       get_product_expiration_month(get_op_product(last_op)),
                                       get_product_expiration_year(get_op_product(last_op)));
        update_product_in_repo(srv->repo, copy);
        destroy_product(old);
        destroy_op(last_op);
        delete_elem_from_position(get_redo_list(srv->undo_redo), get_dynamic_array_size(get_redo_list(srv->undo_redo)) - 1);
    }
    return 0;
}

int srv_add_product(Service *srv, char *name, int category, double quantity, int d, int m, int y) {
    Product *old_product, *p = create_product(name, category, quantity, d, m, y);
    int valid_score = validate_product(p);
    if (valid_score < 0) {
        destroy_product(p);
        return valid_score;
    }
    old_product = find_product_in_repo(srv->repo, name, category);
    if (old_product == NULL) {
        // If the product is not already in the repository, we simply add it
//        clear_history_states(srv->states_for_redo);   // STATE SAVER UNDO
//        save_current_state_as_undo(srv);              //
        add_product_to_repo(srv->repo, p);
        undo_add(srv->undo_redo, p);        // todo:
        clear_redo_list(srv->undo_redo);    // todo:
        return 0;
    } else {
        // If the product is already in the repository, we update it with increased quantity
        double old_quantity = get_product_quantity(old_product);
        set_product_quantity(p, old_quantity + quantity);
//        clear_history_states(srv->states_for_redo);       // STATE SAVER UNDO
//        save_current_state_as_undo(srv);                  // STATE SAVER UNDO
        update_product_in_repo(srv->repo, p);
        undo_update(srv->undo_redo, old_product);        // todo:
        clear_redo_list(srv->undo_redo);                // todo:
        destroy_product(old_product);
        return 1;
    }
}

int srv_remove_product(Service *srv, char *name, int category) {
    Product *product_to_remove = find_product_in_repo(srv->repo, name, category);
    if (product_to_remove == NULL) {
        return -1;
    }
//    clear_history_states(srv->states_for_redo);       // STATE SAVER UNDO
//    save_current_state_as_undo(srv);                  // STATE SAVER UNDO
    remove_product_from_repo(srv->repo, name, category);
    undo_remove(srv->undo_redo, product_to_remove);     // todo:
    clear_redo_list(srv->undo_redo);                    // todo:
    destroy_product(product_to_remove);
    return 0;
}

int srv_update_product(Service *srv, char *name, int category, double quantity, int d, int m, int y) {
    int new_day, new_month, new_year, update_response;
    Product *old_product = find_product_in_repo(srv->repo, name, category);
    double new_quantity;
    if (old_product == NULL) {
        return -1;
    }
    (fabs(quantity) < 0.0001) ? (new_quantity = get_product_quantity(old_product)) : (new_quantity = quantity);
    (d == 0) ? (new_day = get_product_expiration_day(old_product)) : (new_day = d);
    (m == 0) ? (new_month = get_product_expiration_month(old_product)) : (new_month = m);
    (y == 0) ? (new_year = get_product_expiration_year(old_product)) : (new_year = y);
    Product *new_product = create_product(name, category, new_quantity, new_day, new_month, new_year);

    // We have to save the state of the repository BEFORE applying the update
    // So first we check to see if the update will take place (i.e., if the element is in the repository)
    // If it is, then we save the state of the repo
//    if (find_product_in_repo(srv->repo, name, category) != NULL) {        // STATE SAVER UNDO
//        clear_history_states(srv->states_for_redo);                       // STATE SAVER UNDO
//        save_current_state_as_undo(srv);                                  // STATE SAVER UNDO
//    }
    undo_update(srv->undo_redo, old_product);   // todo:
    clear_redo_list(srv->undo_redo);            // todo:

    update_response = update_product_in_repo(srv->repo, new_product);
    destroy_product(old_product);
    if (update_response == -1) {
        destroy_product(new_product);
    }
    return update_response;
}

int srv_get_no_products(Service *srv) {
    return get_repository_size(srv->repo);
}

void free_all_products(DynamicArray *da) {
    for (int i = 0; i < get_dynamic_array_size(da); i++) {
        destroy_product(get_elem_from_position(da, i));
    }
}

void generic_sort_products(DynamicArray *products, int(*comparator)(const void *, const void *)) {
    qsort(get_dynamic_array_elems(products), get_dynamic_array_size(products), sizeof(Product *), comparator);
}

void filter_by_name(DynamicArray *products, DynamicArray *result, char *str, int (*filter)(Product *, char *)) {
    char string_copy[256];
    Product *current_product;
    strcpy(string_copy, str);
    for (int i = 0; i < get_dynamic_array_size(products); i++) {
        current_product = (Product *) get_elem_from_position(products, i);
        if (filter(current_product, string_copy) > 0) {
            add_elem_to_dynamic_array(result, current_product);
        }
    }
}

int filter_by_category(DynamicArray *products, DynamicArray *result, int category, int (*filter)(Product *, int)) {
    if (validate_category(category) == 1) {
        return 1;
    }
    Product *current_product;
    for (int i = 0; i < get_dynamic_array_size(products); i++) {
        current_product = (Product *) get_elem_from_position(products, i);
        if (category == -1 || filter(current_product, category) > 0) {
            add_elem_to_dynamic_array(result, current_product);
        }
    }
    return 0;
}

int filter_by_expiration(DynamicArray *products, DynamicArray *result, int nr_days, int (*filter)(Product *, int)) {
    if (nr_days < 0) {
        return 1;
    }
    Product *current_product;
    for (int i = 0; i < get_dynamic_array_size(products); i++) {
        current_product = (Product *) get_elem_from_position(products, i);
        if (filter(current_product, nr_days) > 0) {
            add_elem_to_dynamic_array(result, current_product);
        }
    }
    return 0;
}

int filter_by_quantity(DynamicArray *products, DynamicArray *result, double quant, int (*filter)(Product *, double)) {
    if (quant < 0) {
        return 1;
    }
    Product *current_product;
    for (int i = 0; i < get_dynamic_array_size(products); i++) {
        current_product = (Product *) get_elem_from_position(products, i);
        if (filter(current_product, quant) > 0) {
            add_elem_to_dynamic_array(result, current_product);
        }
    }
    return 0;
}

DynamicArray *get_service_products(Service *srv) {
    return get_repository_elems(srv->repo);
}