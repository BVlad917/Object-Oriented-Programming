//
// Created by VladB on 19-Mar-21.
//

#include <iostream>
#include <sstream>
#include <vector>

#include "trench_coat.h"

TrenchCoat::TrenchCoat() = default;

TrenchCoat::TrenchCoat(std::string size, std::string colour, double price, int quantity, std::string photograph) :
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

bool TrenchCoat::operator==(const TrenchCoat &other) {
    return this->size == other.size && this->colour == other.colour;
}

bool TrenchCoat::operator!=(TrenchCoat &other) {
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &out, const TrenchCoat &t) {
    out << t.size << "," << t.colour << "," << t.price << "," << t.quantity << "," << t.photograph;
    return out;
}

std::vector<std::string> tokenize(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

std::istream &operator>>(std::istream &in, TrenchCoat &t) {
    std::string line;
    std::getline(in, line);
    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 5)  {
        return in;
    }
    t.size = tokens[0];
    t.colour = tokens[1];
    t.price = std::stof(tokens[2]);
    t.quantity = std::stoi(tokens[3]);
    t.photograph = tokens[4];
    return in;
}

int TrenchCoat::get_trench_quantity() const {
    return this->quantity;
}

double TrenchCoat::get_trench_price() const {
    return this->price;
}

std::string TrenchCoat::get_trench_size() const{
    return this->size;
}

std::string TrenchCoat::get_trench_colour() const{
    return this->colour;
}

std::string TrenchCoat::get_trench_photograph() const{
    return this->photograph;
}
