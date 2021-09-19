//
// Created by VladB on 30-Mar-21.
//

#include <string>
#include <sstream>
#include <fstream>

#include "file_repository.h"

void FileRepository::read_from_file() {
    std::ifstream fin(this->file_name);
    // We empty the current dynamic vector of trench coats so that everything will be synchronized after the read.
    this->trench_coats.clear_dynamic_vector();
    std::string line;
    TrenchCoat t;
    while (fin >> t) {
        this->trench_coats.add_to_dynamic_vector(t);
    }
    fin.close();
}

void FileRepository::write_to_file() {
    std::ofstream fout(this->file_name);
    for (auto & trench_coat : this->trench_coats) {
        fout << trench_coat << "\n";
    }
    fout.close();
}

void FileRepository::add_trench_to_repo(const TrenchCoat &t) {
    this->read_from_file();
    Repository::add_trench_to_repo(t);
    this->write_to_file();
}

TrenchCoat FileRepository::find_trench_coat(std::string &size, std::string &colour) {
    this->read_from_file();
    return Repository::find_trench_coat(size, colour);
}

void FileRepository::remove_trench_from_repo(TrenchCoat &t) {
    this->read_from_file();
    Repository::remove_trench_from_repo(t);
    this->write_to_file();
}

void FileRepository::update_trench_in_repo(TrenchCoat &t) {
    this->read_from_file();
    Repository::update_trench_in_repo(t);
    this->write_to_file();
}

int FileRepository::get_repository_size() {
    this->read_from_file();
    return Repository::get_repository_size();
}

DynamicVector<TrenchCoat> FileRepository::get_repository_trenches() {
    this->read_from_file();
    return Repository::get_repository_trenches();
}
