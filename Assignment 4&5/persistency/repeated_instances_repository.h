//
// Created by VladB on 29-Mar-21.
//

#ifndef A45_BVLAD917_REPEATED_INSTANCES_REPOSITORY_H
#define A45_BVLAD917_REPEATED_INSTANCES_REPOSITORY_H


#include "repository.h"

class RepeatedInstancesRepository : public Repository {
public:
    void add_trench_to_repo(const TrenchCoat &t) override;

    int count_same_coat_in_repo(TrenchCoat &t);
};


#endif //A45_BVLAD917_REPEATED_INSTANCES_REPOSITORY_H
