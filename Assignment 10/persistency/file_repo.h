//
// Created by VladB on 17-Apr-21.
//

#ifndef A67_BVLAD917_FILE_REPO_H
#define A67_BVLAD917_FILE_REPO_H


#include "in_memory_repo.h"

class FileRepo : public InMemoryRepo {
protected:
    std::string file_name;

    virtual void read_from_file();

    virtual void write_to_file();

public:

    explicit FileRepo(std::string &file_name) : file_name(std::move(file_name)) {};

    TrenchCoat find_trench_coat(std::string &size, std::string &colour) override;

    void add_trench_to_repo(const TrenchCoat &t) override;

    TrenchCoat remove_trench_from_repo(TrenchCoat &t) override;

    TrenchCoat update_trench_in_repo(TrenchCoat &t) override;

    int get_repository_size() override;

    std::vector<TrenchCoat> get_repository_trenches() override;

    virtual void open_file_with_app();

    static std::vector<std::string> tokenize(const std::string &str, char delimiter);
};


#endif //A67_BVLAD917_FILE_REPO_H
