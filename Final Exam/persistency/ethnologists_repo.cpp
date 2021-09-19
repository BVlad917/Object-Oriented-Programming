//
// Created by VladB on 22-Jun-21.
//

#include "ethnologists_repo.h"

#include <utility>
#include <fstream>
#include <algorithm>

EthnologistsRepo::EthnologistsRepo(std::string fileName): fileName{std::move(fileName)} {
    this->readFile();
}

void EthnologistsRepo::readFile() {
    std::ifstream fin(this->fileName);
    if (!fin.is_open()) {
        throw std::runtime_error("ERROR! Failed to open ethnologists file on read.");
    }
    this->allEthnologists.clear();
    Ethnologist e;
    while (fin >> e) {
        this->allEthnologists.push_back(e);
    }
    fin.close();
}

std::vector<Ethnologist> EthnologistsRepo::getAllEthnologists() {
    return this->allEthnologists;
}

Ethnologist &EthnologistsRepo::findEthnologistByName(std::string name) {
    Ethnologist dummy{std::move(name), "ta"};
    auto it = std::find(this->allEthnologists.begin(), this->allEthnologists.end(), dummy);
    if (it != this->allEthnologists.end()) {
        return *it;
    } else {
        throw std::runtime_error("ERROR! Failed to find the ethnologist in the repository.");
    }
}
