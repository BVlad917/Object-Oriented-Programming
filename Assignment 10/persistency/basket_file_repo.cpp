//
// Created by VladB on 17-Apr-21.
//

#include <fstream>
#include <algorithm>
#include "basket_file_repo.h"
#include "../errors/exceptions.h"

BasketFileRepo::BasketFileRepo(std::string &file_name) : FileRepo(file_name) {
    std::ofstream fout(this->file_name);
    if (!fout.is_open()) {
        throw RepositoryException("\nERROR: The file could not be opened.\n");
    }
    fout << "";
    fout.close();
};

void BasketFileRepo::add_trench_to_repo(const TrenchCoat &t) {
    this->read_from_file();
    if (this->count_same_coat_in_repo(t) == t.get_trench_quantity()) {
        throw RepositoryException("\nCannot add to the shopping cart. Not enough coats in the store.\n");
    }
    auto position = std::find(this->trench_coats.begin(), this->trench_coats.end(), t);
    this->trench_coats.insert(position, t);
    this->write_to_file();
}

void BasketFileRepo::update_all(TrenchCoat &t) {
    this->read_from_file();
    for (auto it = this->trench_coats.begin(); it != this->trench_coats.end(); it++) {
        if ((*it) == t) {
            this->trench_coats.at(it - this->trench_coats.begin()) = t;
        }
    }
    this->write_to_file();
}

int BasketFileRepo::count_same_coat_in_repo(const TrenchCoat &t) {
    this->read_from_file();
    int cnt = 0;
    for (auto & trench_coat : this->trench_coats) {
        if (trench_coat == t) {
            cnt += 1;
        }
    }
    return cnt;
}
