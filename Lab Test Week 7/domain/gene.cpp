//
// Created by VladB on 05-Apr-21.
//

#include "gene.h"

Gene::Gene() = default;

Gene::Gene(std::string organism, std::string name, std::string sequence) :
        organism(std::move(organism)), name(std::move(name)), sequence(std::move(sequence)) {}

std::string Gene::get_sequence() {
    return this->sequence;
}

bool Gene::operator==(Gene &other) {
    return this->name == other.name && this->organism == other.organism;
}

std::string Gene::get_organism() {
    return this->organism;
}

std::string Gene::get_name() {
    return this->name;
}


