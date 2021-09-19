//
// Created by VladB on 19-Mar-21.
//

#include <iostream>
#include <sstream>
#include <vector>

#include "trench_coat.h"
#include "../errors/exceptions.h"

TrenchCoat::TrenchCoat() = default;

TrenchCoat::TrenchCoat(std::string size, std::string colour, double price, int quantity, std::string photograph):
price(price), quantity(quantity), photograph(std::move(photograph)) {
    // Store the size in all capital letters
    for (auto &c : size) c = toupper(c);
    this->size = size;
    // Store the colour in title case (first letter capital, other letters lower case)
    for (std::string::size_type i = 0; i < colour.size(); i++) {
        if (i == 0 || (i > 0 && colour[i - 1] == ' ')) colour[i] = toupper(colour[i]);
        else colour[i] = tolower(colour[i]);
    }
    this->colour = colour;
}

bool TrenchCoat::operator==(TrenchCoat &other) {
    return this->size == other.size && this->colour == other.colour;
}

bool TrenchCoat::operator!=(TrenchCoat &other) {
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &out, const TrenchCoat &t) {
    out << t.size << "," << t.colour << "," << t.price << "," << t.quantity << "," << t.photograph;
    return out;
}

std::istream &operator>>(std::istream &in, TrenchCoat &t) {
    std::vector<std::string> fields;
    std::string str, sub_str, size, colour, photo;
    int quantity;
    double price;
    in >> str;
    std::stringstream str_stream(str);
    while (str_stream.good()) {
        std::getline(str_stream, str, ',');
        fields.push_back(str);
    }
    if (fields.size() != 5) {
        return in;
    }
    size = fields[0];
    colour = fields[1];
    price = std::stof(fields[2]);
    quantity = std::stoi(fields[3]);
    photo = fields[4];
    t = TrenchCoat(size, colour, price, quantity, photo);
    return in;
}

int TrenchCoat::get_trench_quantity() const {
    return this->quantity;
}

double TrenchCoat::get_trench_price() const {
    return this->price;
}

std::string TrenchCoat::get_trench_size() {
    return this->size;
}

std::string TrenchCoat::get_trench_colour() {
    return this->colour;
}

std::string TrenchCoat::get_trench_photograph() {
    return this->photograph;
}
