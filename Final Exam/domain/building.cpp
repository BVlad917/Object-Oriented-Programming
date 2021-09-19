//
// Created by VladB on 22-Jun-21.
//

#include "building.h"

#include <sstream>

Building::Building(int id, std::string desc, std::string ta, std::vector<std::string> loc)
    : id{id}, description{std::move(desc)}, thematicArea{std::move(ta)}, location{std::move(loc)} {}

int Building::getId() const {
    return id;
}

const std::string &Building::getDescription() const {
    return description;
}

const std::string &Building::getThematicArea() const {
    return thematicArea;
}

const std::vector<std::string> &Building::getLocation() const {
    return location;
}

std::vector<std::string> second_tokenize(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

std::istream &operator>>(std::istream &in, Building &p) {
    std::string line;
    std::getline(in, line);
    std::vector<std::string> tokens = second_tokenize(line, ';');
    if (tokens.size() < 4)  {
        return in;
    }
    p.location.clear();
    p.id = std::stoi(tokens[0]);
    p.description = tokens[1];
    p.thematicArea = tokens[2];
    for (int i = 3; i < tokens.size(); i++) {
        p.location.push_back(tokens[i]);
    }
    return in;
}

bool Building::operator==(const Building &other) const {
    return this->id == other.id;
}
