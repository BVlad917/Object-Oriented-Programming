//
// Created by VladB on 17-Apr-21.
//

#include <fstream>
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
    this->trench_coats.push_back(t);
    this->write_to_file();
}

int BasketFileRepo::count_same_coat_in_repo(const TrenchCoat &t) {
    int cnt = 0;
    for (auto & trench_coat : this->trench_coats) {
        if (trench_coat == t) {
            cnt += 1;
        }
    }
    return cnt;
}

