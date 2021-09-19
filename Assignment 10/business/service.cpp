//
// Created by VladB on 20-Mar-21.
//

#include <cmath>
#include <algorithm>
#include <fstream>

#include "service.h"
#include "../errors/exceptions.h"
#include "../actions/action_add.h"
#include "../actions/action_remove.h"
#include "../actions/action_update.h"

Service::Service(AbstractRepository &repo, BasketFileRepo &cart)
        : repo(repo), shopping_cart_repo{cart}, permissions("User") {}

void Service::change_app_permissions(const std::string &new_permissions) {
    if (new_permissions != "User" && new_permissions != "Admin") {
        throw ServiceException("Error! Invalid app permissions given.\n");
    }
    this->permissions = new_permissions;
}

std::string Service::get_app_permissions() {
    return this->permissions;
}

void Service::add_trench(std::string size, std::string colour, double price, int quantity, std::string photo) {
    TrenchCoat t1(std::move(size), std::move(colour), price, quantity, std::move(photo));
    TrenchCoatValidator::validate(t1);
    this->repo.add_trench_to_repo(t1);

    this->undo_stack.push(std::make_unique<ActionAdd>(this->repo, t1));  // Add a new op to the undo stack
    // Every time we perform an action that is not a redo action (so every time an action is called as a service
    // function) we clear the whole redo stack. This is the only way the Undo-Redo functionalities will work
    // in the way we intend (like an undo-redo functionality in Paint, or any other software)
    while (!this->redo_stack.empty()) {
        this->redo_stack.pop();
    }
}

void Service::remove_trench(std::string size, std::string colour) {
    TrenchCoat t1(size, colour, 1, 1, "dummy_photo");
    TrenchCoatValidator::validate(t1);
    TrenchCoat removed_coat = this->repo.remove_trench_from_repo(t1);

    this->undo_stack.push(std::make_unique<ActionRemove>(this->repo, removed_coat));  // Add a new op to the undo stack
    // Every time we perform an action that is not a redo action we clear the whole redo stack
    while (!this->redo_stack.empty()) {
        this->redo_stack.pop();
    }
    try {
        this->shopping_cart_repo.remove_trench_from_repo(removed_coat);   // Also remove it from the shopping cart
    }
    catch (RepositoryException &) {
        // The trench coat we remove might not be in the shopping cart, but we don't have to throw an exception or
        // do anything differently in that case, we just try to also remove it from the shopping cart
    }
}

void Service::update_trench(std::string size, std::string colour, double price, int quantity, std::string photo) {
    TrenchCoat old_trench_coat = this->repo.find_trench_coat(size, colour);
    if (fabs(price) < 0.00001) price = old_trench_coat.get_trench_price();
    if (quantity == 0) quantity = old_trench_coat.get_trench_quantity();
    if (photo.length() == 0) photo = old_trench_coat.get_trench_photograph();
    TrenchCoat new_trench_coat(std::move(size), std::move(colour), price, quantity, photo);
    TrenchCoatValidator::validate(new_trench_coat);
    this->repo.update_trench_in_repo(new_trench_coat);

    // Add a new op to the undo stack
    this->undo_stack.push(std::make_unique<ActionUpdate>(this->repo, old_trench_coat, new_trench_coat));
    // Every time we perform an action that is not a redo action we clear the whole redo stack
    while (!this->redo_stack.empty()) {
        this->redo_stack.pop();
    }
    // Don't forget to also update the coats that match the updated coat in the shopping basket
    this->shopping_cart_repo.update_all(new_trench_coat);
}

std::vector<TrenchCoat> Service::get_all_trenches_from_repo() {
    return this->repo.get_repository_trenches();
}

std::vector<TrenchCoat> Service::get_all_trenches_from_shopping_cart() {
    return this->shopping_cart_repo.get_repository_trenches();
}

std::vector<TrenchCoat> Service::filter_by(const AbstractFilter &filter) {
    std::vector<TrenchCoat> result;
    std::vector<TrenchCoat> all_trenches = this->get_all_trenches_from_repo();
    std::copy_if(all_trenches.begin(), all_trenches.end(), std::back_inserter(result),
                 [&filter](const TrenchCoat& t) { return filter.include(t); });
    return result;
}

void Service::put_trench_in_shopping_cart(TrenchCoat &t) {
    this->shopping_cart_repo.add_trench_to_repo(t);
    this->undo_cart_stack.push(std::make_unique<ActionAdd>(this->shopping_cart_repo, t));
    // Don't forget to clear the redo stack every time we perform an action that is not an undo
    // operation
    while (!this->redo_cart_stack.empty()) {
        this->redo_cart_stack.pop();
    }
}

void Service::remove_trench_from_shopping_cart(TrenchCoat& t) {
    TrenchCoat removed_coat = this->shopping_cart_repo.remove_trench_from_repo(t);
    this->undo_cart_stack.push(std::make_unique<ActionRemove>(this->shopping_cart_repo, removed_coat));
    // Don't forget to clear the redo stack every time we perform an action that is not an undo
    // operation
    while (!this->redo_cart_stack.empty()) {
        this->redo_cart_stack.pop();
    }
}

double Service::get_total_price() {
    double sum = 0;
    std::vector<TrenchCoat> all_trenches_in_cart = this->shopping_cart_repo.get_repository_trenches();
    for (auto &it : all_trenches_in_cart) {
        sum += it.get_trench_price();
    }
    return sum;
}

void Service::fill_repo(const std::string& fill_file_name) {
    std::ifstream fin(fill_file_name);
    if (!fin.is_open()) {
        throw RepositoryException("\nERROR: The file could not be opened.\n");
    }
    this->repo.clear_repository();
    TrenchCoat t;
    while (fin >> t) {
        this->repo.add_trench_to_repo(t);
    }
    fin.close();
}

void Service::open_shopping_basket_file() {
    this->shopping_cart_repo.open_file_with_app();
}

void Service::admin_undo() {
    if (this->undo_stack.empty()) {
        throw ServiceException("\nERROR: The undo stack is empty. Cannot undo.\n");
    }
    this->undo_stack.top()->execute_undo();
    this->redo_stack.push(std::move(this->undo_stack.top()));
    this->undo_stack.pop();
}

void Service::admin_redo() {
    if (this->redo_stack.empty()) {
        throw ServiceException("\nERROR: The redo stack is empty. Cannot redo.\n");
    }
    this->redo_stack.top()->execute_redo();
    this->undo_stack.push(std::move(this->redo_stack.top()));
    this->redo_stack.pop();
}

void Service::user_undo() {
    if (this->undo_cart_stack.empty()) {
        throw ServiceException("\nERROR: The undo stack is empty. Cannot undo.\n");
    }
    this->undo_cart_stack.top()->execute_undo();
    this->redo_cart_stack.push(std::move(this->undo_cart_stack.top()));
    this->undo_cart_stack.pop();
}

void Service::user_redo() {
    if (this->redo_cart_stack.empty()) {
        throw ServiceException("\nERROR: The redo stack is empty. Cannot redo.\n");
    }
    this->redo_cart_stack.top()->execute_redo();
    this->undo_cart_stack.push(std::move(this->redo_cart_stack.top()));
    this->redo_cart_stack.pop();
}

