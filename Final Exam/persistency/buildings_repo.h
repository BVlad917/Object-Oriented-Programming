//
// Created by VladB on 22-Jun-21.
//

#ifndef E2_BVLAD917_BUILDINGS_REPO_H
#define E2_BVLAD917_BUILDINGS_REPO_H


#include <vector>
#include <building.h>

class BuildingsRepo {
private:
    std::vector<Building> allBuildings;
    std::string fileName;
    void readFile();

public:
    explicit BuildingsRepo(std::string fileName);

    std::vector<Building> getAllBuildings();

    bool isBuildingInRepo(Building building);

    Building& findBuildingById(int id);

    void addLocation(Building& newBuilding);

    std::vector<Building>::iterator removeBuilding(Building& newBuilding);
};


#endif //E2_BVLAD917_BUILDINGS_REPO_H
