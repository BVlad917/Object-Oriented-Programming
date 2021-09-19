//
// Created by VladB on 05-Apr-21.
//

#ifndef T1_BVLAD917_1_SERVICE_H
#define T1_BVLAD917_1_SERVICE_H


#include "../persistency/repository.h"

class Service {
private:
    Repository &repo;

    /*
        Given 2 strings x and y, finds the longest common substring of the 2 strings. Returns the string "-1" if
        there is no common substring between the 2 strings.
     */
    static std::string longest_common_substr(std::string x, std::string y);

public:
    explicit Service(Repository &repo);

    /*
    Adds a new gene to the repository.
    Input:  organism - string, the name of the gene's organism
            name - string, the name of the gene itself
            sequence - string, the gene's sequence
    */
    void srv_add_gene(std::string organism, std::string name, std::string sequence);

    DynamicArray get_decreasing_genes();

    DynamicArray filtered_genes(const std::string &sub_seq);

    /*
        Searches for a gene in the repository using the gene identifiers.
        Input: organism - string, the name of the gene's organism; name - string, the name of the gene
        Output: The gene in the repository with the given attributes
        Throws: Exception if no gene in the repository is found with the given attributes
     */
    Gene find_gene(const std::string &organism, const std::string &name);

    std::string longest_subseq_of_gene_pair(const std::string &, const std::string &, const std::string &,
                                            const std::string &);

    void fill_repo();
};


#endif //T1_BVLAD917_1_SERVICE_H
