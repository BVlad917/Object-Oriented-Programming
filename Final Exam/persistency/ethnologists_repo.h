//
// Created by VladB on 22-Jun-21.
//

#ifndef E2_BVLAD917_ETHNOLOGISTS_REPO_H
#define E2_BVLAD917_ETHNOLOGISTS_REPO_H


#include <vector>
#include <ethnologist.h>

class EthnologistsRepo {
private:
    std::vector<Ethnologist> allEthnologists;
    std::string fileName;
    void readFile();

public:
    explicit EthnologistsRepo(std::string fileName);

    std::vector<Ethnologist> getAllEthnologists();

    Ethnologist& findEthnologistByName(std::string name);
};


#endif //E2_BVLAD917_ETHNOLOGISTS_REPO_H
