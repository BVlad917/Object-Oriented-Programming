//
// Created by VladB on 05-Apr-21.
//

#include "repository.h"

Repository::Repository() = default;

void Repository::repo_add_gene(Gene &new_gene) {
    if (this->genes.find_position_of_elem(new_gene) != -1) {
        throw std::runtime_error("\nERROR: Gene already in the repository.\n");
    }
    this->genes.add_to_dynamic_array(new_gene);
}

DynamicArray Repository::get_all_genes_from_repo() {
    return this->genes;
}
