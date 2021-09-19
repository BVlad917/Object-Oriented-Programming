//
// Created by VladB on 20-Mar-21.
//

#include <cmath>
#include <algorithm>
#include <fstream>

#include "service.h"
#include "../errors/exceptions.h"

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
}

void Service::remove_trench(std::string size, std::string colour) {
    TrenchCoat t1(std::move(size), std::move(colour), 1, 1, "dummy_photo");
    TrenchCoatValidator::validate(t1);
    this->repo.remove_trench_from_repo(t1);
    try {
        this->shopping_cart_repo.remove_trench_from_repo(t1);   // Also remove it from the shopping cart
    }
    catch (RepositoryException &) {
        // The trench coat we remove might not be in the shopping cart
    }
}

void Service::update_trench(std::string size, std::string colour, double price, int quantity, std::string photo) {
    TrenchCoat old_trench_coat = this->repo.find_trench_coat(size, colour);
    if (fabs(price) < 0.00001) price = old_trench_coat.get_trench_price();
    if (quantity == 0) quantity = old_trench_coat.get_trench_quantity();
    if (photo.length() == 0) photo = old_trench_coat.get_trench_photograph();
    TrenchCoat t1(std::move(size), std::move(colour), price, quantity, photo);
    TrenchCoatValidator::validate(t1);
    this->repo.update_trench_in_repo(t1);
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
    if (this->shopping_cart_repo.count_same_coat_in_repo(t) == t.get_trench_quantity()) {
        throw ServiceException{"\nCannot add to the shopping cart. Not enough coats in the store.\n"};
    }
    this->shopping_cart_repo.add_trench_to_repo(t);
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
