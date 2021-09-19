//
// Created by VladB on 17-Apr-21.
//

#include <algorithm>
#include "in_memory_repo.h"
#include "../errors/exceptions.h"

TrenchCoat InMemoryRepo::find_trench_coat(std::string &size, std::string &colour) {
    TrenchCoat dummy(size, colour, 100, 100, "dummy_link");
    auto trench_it = std::find(this->trench_coats.begin(), this->trench_coats.end(), dummy);
    if (trench_it == this->trench_coats.end()) {
        throw RepositoryException("\nError! The trench coat is not in the store.\n");
    }
    return *trench_it;
}

void InMemoryRepo::add_trench_to_repo(const TrenchCoat &t) {
    if (std::find(this->trench_coats.begin(), this->trench_coats.end(), t) != this->trench_coats.end()) {
        throw RepositoryException("\nError! Cannot add. Trench Coat already in the store.\n");
    }
    this->trench_coats.push_back(t);
}

void InMemoryRepo::remove_trench_from_repo(TrenchCoat &t) {
    auto position = std::find(this->trench_coats.begin(), this->trench_coats.end(), t);
    if (position == this->trench_coats.end()) {
        throw RepositoryException("\nError! Cannot remove. Trench Coat not in the store.\n");
    }
    this->trench_coats.erase(position);
}

void InMemoryRepo::update_trench_in_repo(TrenchCoat &t) {
    auto position = std::find(this->trench_coats.begin(), this->trench_coats.end(), t);
    if (position == this->trench_coats.end()) {
        throw RepositoryException("\nError! Cannot update. The trench coat is not in the store.\n");
    }
    this->trench_coats.at(position - this->trench_coats.begin()) = t;
}

int InMemoryRepo::get_repository_size() {
    return (int) (this->trench_coats.size());
}

std::vector<TrenchCoat> InMemoryRepo::get_repository_trenches() {
    return this->trench_coats;
}

void InMemoryRepo::clear_repository() {
    this->trench_coats.clear();
}

