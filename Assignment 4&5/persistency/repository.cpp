//
// Created by VladB on 20-Mar-21.
//

#include <iostream>

#include "repository.h"

Repository::Repository() = default;

TrenchCoat Repository::find_trench_coat(std::string &size, std::string &colour) {
    TrenchCoat dummy(size, colour, 100, 100, "dummy_link");
    int trench_index = this->trench_coats.find_position_of_elem(dummy);
    if (trench_index == -1) {
        throw RepositoryException("\nError! The trench coat is not in the store.\n");
    }
    return this->trench_coats[trench_index];
}

void Repository::add_trench_to_repo(const TrenchCoat& t) {
    if (this->trench_coats.find_position_of_elem(t) != -1) {
        throw RepositoryException("\nError! Cannot add. Trench Coat already in the store.\n");
    }
    this->trench_coats.add_to_dynamic_vector(t);
}

void Repository::remove_trench_from_repo(TrenchCoat &t) {
    int position = this->trench_coats.find_position_of_elem(t);
    if (position == -1) {
        throw RepositoryException("\nError! Cannot remove. Trench Coat not in the store.\n");
    }
    this->trench_coats.remove_elem_from_position_in_dynamic_vector(position);
}

void Repository::update_trench_in_repo(TrenchCoat &t) {
    int position = this->trench_coats.find_position_of_elem(t);
    if (position == -1) {
        throw RepositoryException("\nError! Cannot update. The trench coat is not in the store.\n");
    }
    this->trench_coats.update_elem_in_dynamic_vector(t, position);
}

int Repository::get_repository_size() {
    return this->trench_coats.get_dynamic_vector_size();
}

DynamicVector<TrenchCoat> Repository::get_repository_trenches() {
    return this->trench_coats;
}
