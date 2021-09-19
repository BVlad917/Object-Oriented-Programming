//
// Created by VladB on 30-Mar-21.
//

#ifndef A45_BVLAD917_FILE_REPOSITORY_H
#define A45_BVLAD917_FILE_REPOSITORY_H

#include "repository.h"

#include <utility>

class FileRepository : public Repository {
private:
    std::string file_name;

    void read_from_file();

    void write_to_file();

public:
    explicit FileRepository(std::string file_name) : file_name(std::move(file_name)) { this->read_from_file(); }

    TrenchCoat find_trench_coat(std::string &size, std::string &colour) override;

    void add_trench_to_repo(const TrenchCoat &t) override;

    void remove_trench_from_repo(TrenchCoat &t) override;

    void update_trench_in_repo(TrenchCoat &t) override;

    int get_repository_size() override;

    DynamicVector<TrenchCoat> get_repository_trenches() override;

};


#endif //A45_BVLAD917_FILE_REPOSITORY_H
