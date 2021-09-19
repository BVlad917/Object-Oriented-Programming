//
// Created by VladB on 17-Apr-21.
//

#include <fstream>
#include "basket_csv_repo.h"
#include "../errors/exceptions.h"

BasketCSVRepo::BasketCSVRepo(std::string &file_name) : BasketFileRepo(file_name) {}

void BasketCSVRepo::read_from_file() {
    std::ifstream fin(this->file_name);
    if (!fin.is_open()) {
        throw RepositoryException("\nERROR: The file could not be opened.\n");
    }
    // Empty the current repository of trench coats so that everything will be synchronized
    this->trench_coats.clear();
    TrenchCoat t;
    std::string line, size, color, photo;
    int quantity;
    double price;
    std::vector<std::string> tokens;
    while (fin >> line) {
        tokens = BasketCSVRepo::tokenize(line, ',');
        size = tokens[0];
        color = tokens[1];
        price = std::stof(tokens[2]);
        quantity = std::stoi(tokens[3]);
        photo = tokens[4];
        t = TrenchCoat{size, color, price, quantity, photo};
        this->trench_coats.push_back(t);
    }
    fin.close();
}

void BasketCSVRepo::write_to_file() {
    std::ofstream fout(this->file_name);
    if (!fout.is_open()) {
        throw RepositoryException("\nERROR: The file could not be opened.\n");
    }
    std::string size, color, price, quantity, photo;
    for (auto &trench_coat : this->trench_coats) {
        size = trench_coat.get_trench_size();
        color = trench_coat.get_trench_colour();
        price = std::to_string(trench_coat.get_trench_price());
        quantity = std::to_string(trench_coat.get_trench_quantity());
        photo = trench_coat.get_trench_photograph();
        fout << size << "," << color << "," << price << "," << quantity << "," << photo << "\n";
    }
    fout.close();
}


