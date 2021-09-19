//
// Created by VladB on 22-Jun-21.
//

#ifndef E2_BVLAD917_SERVICE_H
#define E2_BVLAD917_SERVICE_H


#include "../persistency/ethnologists_repo.h"
#include "../persistency/buildings_repo.h"

class Service {
private:
    EthnologistsRepo& ethnologistsRepo;
    BuildingsRepo& buildingsRepo;

public:
    Service(EthnologistsRepo& er, BuildingsRepo& br);

    std::vector<Ethnologist> srvGetAllEthnologists();

    std::vector<Building> srvGetAllBuildings();

    Ethnologist& findEthnologistByName(std::string name);

    void addBuilding(int id, std::string description, std::string thematicSector, std::vector<std::string> locationVec);

    static bool isLocationGood(std::vector<std::string> locationVec);

    bool checkIfLocationUsed(std::vector<std::string> locationVec);

    void updateBuilding(int id, std::string description, std::string thematicSector, std::vector<std::string> locationVec);

    Building srvFindBuildingById(int id);

    std::string findThemeForCell(char letter, char number);
};


#endif //E2_BVLAD917_SERVICE_H
