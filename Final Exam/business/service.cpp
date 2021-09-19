//
// Created by VladB on 22-Jun-21.
//

#include "service.h"

#include <utility>
#include <stdexcept>

Service::Service(EthnologistsRepo &er, BuildingsRepo &br): ethnologistsRepo{er}, buildingsRepo{br} {}

std::vector<Ethnologist> Service::srvGetAllEthnologists() {
    return this->ethnologistsRepo.getAllEthnologists();
}

std::vector<Building> Service::srvGetAllBuildings() {
    return this->buildingsRepo.getAllBuildings();
}

Ethnologist &Service::findEthnologistByName(std::string name) {
    return this->ethnologistsRepo.findEthnologistByName(std::move(name));
}

void Service::addBuilding(int id, std::string description, std::string thematicSector, std::vector<std::string> locationVec) {
    Building dummy{id, description, thematicSector, locationVec};
    if (this->buildingsRepo.isBuildingInRepo(dummy)) {
        throw std::runtime_error("ERROR! Building already in the repository.");
    }
    if (description.empty()) {
        throw std::runtime_error("ERROR! Cannot add a building without a description.");
    }
    if (!this->isLocationGood(locationVec)) {
        throw std::runtime_error("ERROR! Location not continuous");
    }
    if (this->checkIfLocationUsed(locationVec)) {
        throw std::runtime_error("ERROR! Location already used.");
    }
    this->buildingsRepo.addLocation(dummy);
}

bool Service::isLocationGood(std::vector<std::string> locationVec) {
    std::string possibleNeighbour1, possibleNeighbour2, possibleNeighbour3, possibleNeighbour4;
    for (int i = 1; i < locationVec.size(); i++) {
        char letter = locationVec[i][0];
        char number = locationVec[i][1];

        possibleNeighbour1[0] = letter;
        possibleNeighbour1[1] = number - 1;

        possibleNeighbour2[0] = letter - 1;
        possibleNeighbour2[1] = number;

        possibleNeighbour3[0] = letter;
        possibleNeighbour3[1] = number + 1;

        possibleNeighbour4[0] = letter + 1;
        possibleNeighbour4[1] = number;

        char prevLetter = locationVec[i - 1][0];
        char prevNumber = locationVec[i - 1][1];
        bool ok = false;

        if ((prevLetter == possibleNeighbour1[0] && prevNumber == possibleNeighbour1[1]) ||
        (prevLetter == possibleNeighbour2[0] && prevNumber == possibleNeighbour2[1]) ||
        (prevLetter == possibleNeighbour3[0] && prevNumber == possibleNeighbour3[1]) ||
        (prevLetter == possibleNeighbour4[0] && prevNumber == possibleNeighbour4[1])){
            ok = true;
        }

        if (!ok) {
            return false;
        }
    }
    return true;
}

bool Service::checkIfLocationUsed(std::vector<std::string> locationVec) {
    for (auto loc: locationVec) {
        for (auto building: this->buildingsRepo.getAllBuildings()) {
            for (auto place: building.getLocation()) {
                if (loc == place) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Service::updateBuilding(int id, std::string description, std::string thematicSector, std::vector<std::string> locationVec) {
    Building dummy{id, description, thematicSector, locationVec};
    this->buildingsRepo.removeBuilding(dummy);
    this->addBuilding(id, description, thematicSector, locationVec);
}

Building Service::srvFindBuildingById(int id) {
    return this->buildingsRepo.findBuildingById(id);
}

std::string Service::findThemeForCell(char letter, char number) {
    for (auto building: this->buildingsRepo.getAllBuildings()) {
        for (auto spot: building.getLocation()) {
            if (spot[0] == letter && spot[1] == number) {
                return building.getThematicArea();
            }
        }
    }
    return "";
}
