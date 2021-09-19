//
// Created by VladB on 22-Jun-21.
//

#include "buildings_repo.h"

#include <utility>
#include <fstream>
#include <algorithm>

BuildingsRepo::BuildingsRepo(std::string fileName): fileName{std::move(fileName)} {
    this->readFile();
}

void BuildingsRepo::readFile() {
    std::ifstream fin(this->fileName);
    if (!fin.is_open()) {
        throw std::runtime_error("ERROR! Failed to open ethnologists file on read.");
    }
    this->allBuildings.clear();
    Building b;
    while (fin >> b) {
        this->allBuildings.push_back(b);
    }
    fin.close();
}

std::vector<Building> BuildingsRepo::getAllBuildings() {
    return this->allBuildings;
}

bool BuildingsRepo::isBuildingInRepo(Building building) {
    auto it = std::find(this->allBuildings.begin(), this->allBuildings.end(), building);
    if (it != this->allBuildings.end()) {
        return true;
    } else {
        return false;
    }
}

void BuildingsRepo::addLocation(Building &newBuilding) {
    this->allBuildings.insert(this->allBuildings.end() - 1, newBuilding);
}

Building &BuildingsRepo::findBuildingById(int id) {
    Building dummy{id, "some", "time", std::vector<std::string>{"i", "wonder"}};
    auto it = std::find(this->allBuildings.begin(), this->allBuildings.end(), dummy);
    if (it == this->allBuildings.end()) {
        throw std::runtime_error("ERROR! Building not in repo.");
    }
    return *it;
}

std::vector<Building>::iterator BuildingsRepo::removeBuilding(Building &newBuilding) {
    auto it = std::find(this->allBuildings.begin(), this->allBuildings.end(), newBuilding);
    if (it != this->allBuildings.end()) {
        this->allBuildings.erase(it);
    } else {
        throw std::runtime_error("ERROR! Building not in the repository.");
    }
    return it;
}
