//
// Created by VladB on 22-Jun-21.
//

#include "ethnologist.h"

#include <utility>
#include <vector>
#include <sstream>

Ethnologist::Ethnologist(std::string n, std::string ta): name{std::move(n)}, thematicArea{std::move(ta)} {}

const std::string &Ethnologist::getName() const {
    return name;
}

const std::string &Ethnologist::getThematicArea() const {
    return thematicArea;
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

std::istream &operator>>(std::istream &in, Ethnologist &p) {
    std::string line;
    std::getline(in, line);
    std::vector<std::string> tokens = tokenize(line, ';');
    if (tokens.size() != 2)  {
        return in;
    }
    p.name = tokens[0];
    p.thematicArea = tokens[1];
    return in;
}

bool Ethnologist::operator==(const Ethnologist &other) const {
    return this->name == other.name;
}
