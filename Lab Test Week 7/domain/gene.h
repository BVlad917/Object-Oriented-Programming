//
// Created by VladB on 05-Apr-21.
//

#ifndef T1_BVLAD917_1_GENE_H
#define T1_BVLAD917_1_GENE_H

#include <iostream>

class Gene {
private:
    std::string organism, name, sequence;

public:
    Gene();

    Gene(std::string organism, std::string name, std::string sequence);

    std::string get_sequence();

    std::string get_organism();

    std::string get_name();

    bool operator==(Gene &other);
};


#endif //T1_BVLAD917_1_GENE_H
