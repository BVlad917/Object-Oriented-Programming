//
// Created by VladB on 07-Mar-21.
//

#include <stdio.h>

#include "tests/run_all_tests.h"
#include "presentation/ui.h"

#define INITIAL_CAPACITY 4

int main() {
    run_all_tests();
//    printf("Tests done.\n\n");
//    Repository *repo = create_repository(INITIAL_CAPACITY);
//
//    // We add a few products to the repo just so we can show the functionalities
//    // Normally the following lines wouldn't be here
//    Product *p = create_product("beef", 3, 3.5, 17, 5, 2021);
//    add_product_to_repo(repo, p);
//    p = create_product("chicken", 3, 2.75, 20, 5, 2021);
//    add_product_to_repo(repo, p);
//    p = create_product("milk", 1, 4.9, 20, 4, 2021);
//    add_product_to_repo(repo, p);
//    p = create_product("eggs", 1, 0.7, 15, 4, 2021);
//    add_product_to_repo(repo, p);
//    p = create_product("apples", 4, 0.46, 30, 4, 2021);
//    add_product_to_repo(repo, p);
//    p = create_product("yoghurt", 1, 1.0, 30, 6, 2021);
//    add_product_to_repo(repo, p);
//    p = create_product("snickers", 2, 0.25, 15, 7, 2021);
//    add_product_to_repo(repo, p);
//    p = create_product("watermelon", 4, 1.65, 7, 8, 2021);
//    add_product_to_repo(repo, p);
//    p = create_product("deer", 3, 15.3, 4, 6, 2021);
//    add_product_to_repo(repo, p);
//    p = create_product("avocado", 4, 0.65, 2, 9, 2021);
//    add_product_to_repo(repo, p);
//
//    Service *srv = create_service(repo);
//    UI* ui = create_ui(srv);
//    printf("Hi there!\n");
//    run_ui(ui);
//    printf("\nHave a great day!\n");
//
//    // Now the program execution will end, but first we free the memory
//    free_all_products(get_repository_elems(repo));
////    clear_history_states(srv->states_for_redo);
////    clear_history_states(srv->states_for_undo);
//    destroy_undo_redo(srv->undo_redo);
//    destroy_repository(repo);
//    destroy_service(srv);
//    destroy_ui(ui);
    return 0;
}