//
// Created by VladB on 29-Mar-21.
//

#include "repeated_instances_repository.h"

void RepeatedInstancesRepository::add_trench_to_repo(const TrenchCoat &t) {
    this->trench_coats.add_to_dynamic_vector(t);
}

int RepeatedInstancesRepository::count_same_coat_in_repo(TrenchCoat &t) {
    int cnt = 0;
    for (auto & trench_coat : this->trench_coats) {
        if (trench_coat == t) {
            cnt += 1;
        }
    }
    return cnt;
}
