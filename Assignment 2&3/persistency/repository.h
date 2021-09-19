//
// Created by VladB on 07-Mar-21.
//

#ifndef A23_BVLAD917_REPOSITORY_H
#define A23_BVLAD917_REPOSITORY_H

#include "../dynamic_array/dynamic_array.h"
#include "../domain/product.h"

typedef struct {
    DynamicArray *dyn_array;
} Repository;

/// Creates an instance of Repository with the given capacity and returns a pointer to it
Repository *create_repository(int capacity);

/// Frees the memory used by the given repository. It also frees the memory used by the dynamic array from
/// the repository, BUT the elements themselves will not be freed! They need to be freed by whoever created them
void destroy_repository(Repository *repo);

/// Adds a given product to the repository.
/// \return: an integer; -1 if the product is already in the repository and it is not added; 0 if the adding
/// took place
int add_product_to_repo(Repository *repo, Product *p);

/// Removes a product from the repository
/// \return: an integer; 0 - if the removing took place successfully; -1 otherwise (the element didn't exist in
/// the repository)
int remove_product_from_repo(Repository *repo, char *name, int category);

/// Updates a product in the repository
/// \return: an integer; 0 - if the update took place successfully; -1 otherwise (the product to be updated
/// didn't actually exist in the repository)
int update_product_in_repo(Repository *repo, Product *p);

/// Returns a pointer to all the products in the repository. Since the products are themselves kept in
/// the repository by pointers, the return value of this function will have to be a pointer to pointer.
Product **get_repository_products(Repository *repo);

/// Returns a pointer to the dynamic array where the elements in the repository are kept
DynamicArray *get_repository_elems(Repository *repo);

/// Returns the repository size as an integer.
int get_repository_size(Repository *repo);

///
/// \param repo
/// \param name
/// \param category
/// \return
Product* find_product_in_repo(Repository *repo, char *name, int category);

DynamicArray *get_deep_copy_of_products(DynamicArray *da_products);

void change_elems(Repository *repo, DynamicArray *new_elems);

#endif //A23_BVLAD917_REPOSITORY_H
