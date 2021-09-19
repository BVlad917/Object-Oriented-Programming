//
// Created by VladB on 17-Apr-21.
//

#ifndef A67_BVLAD917_IN_MEMORY_REPO_H
#define A67_BVLAD917_IN_MEMORY_REPO_H


#include <vector>
#include "abstract_repository.h"

class InMemoryRepo : public AbstractRepository {

protected:
    std::vector<TrenchCoat> trench_coats;
public:

    /*
        Default repository constructor.
     */
    InMemoryRepo() = default;

    ~InMemoryRepo() override = default;

    TrenchCoat find_trench_coat(std::string &size, std::string &colour) override;

    void add_trench_to_repo(const TrenchCoat &t) override;

    TrenchCoat remove_trench_from_repo(TrenchCoat &t) override;

    TrenchCoat update_trench_in_repo(TrenchCoat &t) override;

    int get_repository_size() override;

    std::vector<TrenchCoat> get_repository_trenches() override;

    void clear_repository() override;

};


#endif //A67_BVLAD917_IN_MEMORY_REPO_H
