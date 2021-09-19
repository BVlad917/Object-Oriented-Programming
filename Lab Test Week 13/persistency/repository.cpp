//
// Created by VladB on 24-May-21.
//

#include "repository.h"

#include <utility>
#include <fstream>

Repository::Repository(std::string fn): file_name{std::move(fn)} {
    this->read_file();
}

std::vector<TimeInterval> Repository::repo_get_all_times() {
    this->read_file();
    return this->all_times;
}

void Repository::read_file() {
    std::ifstream fin(this->file_name);
    if (!fin.is_open()) {
        throw std::runtime_error("\nERROR: Failed to open repository file while reading.\n");
    }
    TimeInterval t;
    this->all_times.clear();
    while (fin >> t) {
        this->all_times.push_back(t);
    }
    fin.close();
}
