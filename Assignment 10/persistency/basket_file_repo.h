//
// Created by VladB on 17-Apr-21.
//

#ifndef A67_BVLAD917_BASKET_FILE_REPO_H
#define A67_BVLAD917_BASKET_FILE_REPO_H


#include "file_repo.h"

class BasketFileRepo : public FileRepo {
public:
    explicit BasketFileRepo(std::string &file_name);

    // We overwrite the add_trench_to_repo method since we can have duplicates in the shopping basket,
    // unlike the FileRepo
    void add_trench_to_repo(const TrenchCoat &t) override;

    /*
     * Update all of the instances of trench coat <t> from the shopping basket. Different from the classic <update>
     * functionality from the repository since the shopping basket accepts duplicates, so we have to potentially
     * update multiple instances. This function is used when the admin updates a trench coat in the repository.
     */
    void update_all(TrenchCoat &t);

    /*
     * Count the number of times trench coat <t> appears in the shopping basket. This function is used to check
     * if we can still add another instance of the trench coat <t> in the shopping cart. In the case that
     * we have as many instances of this trench coat in the shopping cart as the quantity of the trench coat,
     * then we cannot add this instance anymore.
     */
    int count_same_coat_in_repo(const TrenchCoat &t);
};


#endif //A67_BVLAD917_BASKET_FILE_REPO_H
