//
// Created by VladB on 17-Apr-21.
//

#ifndef A67_BVLAD917_BASKET_FILE_REPO_H
#define A67_BVLAD917_BASKET_FILE_REPO_H


#include "file_repo.h"

class BasketFileRepo : public FileRepo {
public:
    explicit BasketFileRepo(std::string &file_name);

    void add_trench_to_repo(const TrenchCoat &t) override;

    int count_same_coat_in_repo(const TrenchCoat &t);
};


#endif //A67_BVLAD917_BASKET_FILE_REPO_H
