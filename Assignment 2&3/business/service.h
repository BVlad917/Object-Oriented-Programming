//
// Created by VladB on 07-Mar-21.
//

#ifndef A23_BVLAD917_SERVICE_H
#define A23_BVLAD917_SERVICE_H

#include "../persistency/repository.h"
#include "../undo_redo_inv_ops/inv_ops_undo_redo.h"

typedef struct {
    Repository *repo;
//    DynamicArray *states_for_undo;
//    DynamicArray *states_for_redo;
    UndoRedo* undo_redo;
} Service;

/// Creates an instance of Service with the given repository.
/// \param repo: Instance of Repository
/// \return Pointer to Service
Service *create_service(Repository *repo);

/// Destroys the service given as argument, deallocating it from memory
/// \param srv: the service to be deallocated
void destroy_service(Service *srv);

void free_all_products(DynamicArray *da);

/// Adds a product to the service repository. If there already exists a product with the given name
/// and category, then the quantity of the new product will simply be added to the old product, without
/// actually adding the new product. The expiration date details will be kept as those of the old product (this
/// is an implementation detail that can be changed)
/// \param srv: the service which will add the element to its repo; instance of Service
/// \param name: the name of the product; char*
/// \param category: the category of the product; int
/// \param quantity: the quantity of the product; double
/// \param d: the expiration day of the product; int
/// \param m: the expiration month of the product; int
/// \param y: the expiration year of the product; int
/// \return an integer: 0 if the product was not already in the service repo and was just added. 1 if the
/// product already existed and its quantity was increased. A negative number if the product validation failed
/// (divisible by 3 if the name is invalid, %5 if the category is invalid, %7 if the quantity is invalid,
/// %11 if the date is invalid)
int srv_add_product(Service *srv, char *name, int category, double quantity, int d, int m, int y);

/// Removes a product from the service repository
/// \param srv: instance of Service; the service from which the product needs to be deleted
/// \param name: char*; the name of the product to be removed
/// \param category: integer; the category of the product to be removed
/// \return an integer: 0 - if the product was successfully removed; 1 - if the removing failed (the product
/// is not in the service repository)
int srv_remove_product(Service *srv, char *name, int category);

/// Updates a product in the service repository
/// \param srv: instance of Service; where the product which needs to be updated is
/// \param name: char*; the name of the product to be updated
/// \param category: int; the category of the product to be updated
/// \param quantity: double; the new quantity of the product
/// \param d: int; the new expiration day of the product
/// \param m: int; the new expiration month of the product
/// \param y: int; the new expiration year of the product
/// \return an integer: -1 - if the product failed to be updated (if the product is not actually in
/// the service repository); 0 - if the product was successfully updated
int srv_update_product(Service *srv, char *name, int category, double quantity, int d, int m, int y);

/// Returns the number of products in the service repository
int srv_get_no_products(Service *srv);

/// Returns a pointer to dynamic array to all the products in the service repository
DynamicArray *get_service_products(Service *srv);

/// Generic sorting method for a dynamic array of products
/// \param products: pointer to dynamic array; The array of products which will be sorted
/// \param comparator: pointer to int function; comparator function which decides the order of the elements
void generic_sort_products(DynamicArray *products, int(*comparator)(const void*, const void*));

/// Filters a given dynamic array of products by the product name
/// \param products: pointer to dynamic array; The array of products which will be filtered
/// \param result: pointer to dynamic array; Where the filtered products will be stored
/// \param str: pointer to char; the string used for the filtering process
/// \param filter: pointer to int function; function which decides how the string will be used as filter
void filter_by_name(DynamicArray *products, DynamicArray *result, char* str, int (*filter)(Product*, char*));

/// Filters a given dynamic array of products by the product category
/// \param products: pointer to dynamic array; The array of products which will be filtered
/// \param result: pointer to dynamic array; Where the filtered products will be stored
/// \param category: int; the category used as filter
/// \param filter: pointer to int function; function which decides how the category will be used as filter
/// \return: 0 if the filtering process was successful; 1 otherwise (if the category given by the user is invalid)
int filter_by_category(DynamicArray *products, DynamicArray *result, int category, int (*filter)(Product*, int));

/// Filters a given dynamic array of products by the product expiration date
/// \param products: pointer to dynamic array; The array of products which will be filtered
/// \param result: pointer to dynamic array; Where the filtered products will be stored
/// \param nr_days: int; the number of days used as filter
/// \param filter: pointer to int function; function which decides how the number of days will be used as filter
/// \return: 0 if the filtering process was successful; 1 otherwise (if a negative number is passed as <nr_days>)
int filter_by_expiration(DynamicArray *products, DynamicArray *result, int nr_days, int (*filter)(Product*, int));

/// Filters a given dynamic array of products by the product quantity
/// \param products: pointer to dynamic array; The array of products which will be filtered
/// \param result: pointer to dynamic array; Where the filtered products will be stored
/// \param quant: double; the quantity (in kg) used as filter
/// \param filter: pointer to int function; function which decides how the quantity will be used as filter
/// \return: 0 if the filtering process was successful, 1 otherwise (if a negative number is passed as <quant>)
int filter_by_quantity(DynamicArray *products, DynamicArray *result, double quant, int (*filter)(Product*, double));

///// Applies an undo operation. Brings the state of the repository back to its form before the last performed operation
///// \param srv: pointer to Service; the service where the undo is performed
///// \return: 0 if the undo was successful; 1 otherwise (if there are no more undos to be made)
int apply_undo(Service *srv);

///// Applies a redo operation. Brings the state of the repository back to its form before the last performed undo.
///// \param srv: pointer to Service; the service where the redo is performed
///// \return: 0 if the redo was successful; 1 otherwise (if there are no more redos to be made)
int apply_redo(Service *srv);

///// Frees all the memory taken by a history of states. Used to clear the undo and the redo stack
///// \param history_states: pointer to dynamic array; the history of states which needs to be cleared
void clear_history_states(DynamicArray *history_states);

#endif //A23_BVLAD917_SERVICE_H
