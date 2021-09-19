//
// Created by VladB on 17-Apr-21.
//

#include <fstream>
#include <objbase.h>
#include <sstream>

#include "file_repo.h"
#include "../errors/exceptions.h"

void FileRepo::read_from_file() {
    std::ifstream fin(this->file_name);
    if (!fin.is_open()) {
        throw RepositoryException("\nERROR: The file could not be opened.\n");
    }
    // We empty the current repository of trench coats so that everything will be synchronized after the read.
    this->trench_coats.clear();
    TrenchCoat t;
    while (fin >> t) {
        this->trench_coats.push_back(t);
    }
    fin.close();
}

void FileRepo::write_to_file() {
    std::ofstream fout(this->file_name);
    if (!fout.is_open()) {
        throw RepositoryException("\nERROR: The file could not be opened.\n");
    }
    for (auto &trench_coat : this->trench_coats) {
        fout << trench_coat << "\n";
    }
    fout.close();
}

TrenchCoat FileRepo::find_trench_coat(std::string &size, std::string &colour) {
    this->read_from_file();
    return InMemoryRepo::find_trench_coat(size, colour);
}

void FileRepo::add_trench_to_repo(const TrenchCoat &t) {
    this->read_from_file();
    InMemoryRepo::add_trench_to_repo(t);
    this->write_to_file();
}

TrenchCoat FileRepo::remove_trench_from_repo(TrenchCoat &t) {
    this->read_from_file();
    TrenchCoat removed_coat = InMemoryRepo::remove_trench_from_repo(t);
    this->write_to_file();
    return removed_coat;
}

TrenchCoat FileRepo::update_trench_in_repo(TrenchCoat &t) {
    this->read_from_file();
    TrenchCoat updated_coat = InMemoryRepo::update_trench_in_repo(t);
    this->write_to_file();
    return updated_coat;
}

int FileRepo::get_repository_size() {
    this->read_from_file();
    return InMemoryRepo::get_repository_size();
}

std::vector<TrenchCoat> FileRepo::get_repository_trenches() {
    this->read_from_file();
    return InMemoryRepo::get_repository_trenches();
}

void FileRepo::open_file_with_app() {
    ShellExecute(nullptr, nullptr, this->file_name.c_str(), nullptr, nullptr, SW_SHOW);
}

std::vector<std::string> FileRepo::tokenize(const std::string &str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

