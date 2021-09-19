//
// Created by VladB on 05-Apr-21.
//

#ifndef T1_BVLAD917_1_REPOSITORY_H
#define T1_BVLAD917_1_REPOSITORY_H


#include "../dynamic_vector/dynamic_vector.h"

class Repository {
private:
    DynamicArray genes;
public:
    Repository();

    DynamicArray get_all_genes_from_repo();

    /*
        Adds a new gene to the repository.
        Input: new_gene - an instance of the Gene class.
     */
    void repo_add_gene(Gene& new_gene);
};


#endif //T1_BVLAD917_1_REPOSITORY_H
