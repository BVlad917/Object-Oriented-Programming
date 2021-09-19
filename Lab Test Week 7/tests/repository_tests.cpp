//
// Created by VladB on 05-Apr-21.
//

#include <iostream>
#include <cassert>

#include "repository_tests.h"
#include "../persistency/repository.h"

void RepositoryTests::run_all_repository_tests() {
    std::cout << "Running repository tests...\n";
    RepositoryTests::test_add_gene();
    std::cout << "Repository tests done.\n\n";
}

void RepositoryTests::test_add_gene() {
    Repository repo;
    assert(repo.get_all_genes_from_repo().get_dynamic_array_size() == 0);
    Gene new_gene1{"abc", "def", "ghi"};
    repo.repo_add_gene(new_gene1);
    assert(repo.get_all_genes_from_repo().get_dynamic_array_size() == 1);
    Gene new_gene2{"abc", "xyz", "some_seq"};
    repo.repo_add_gene(new_gene2);
    assert(repo.get_all_genes_from_repo().get_dynamic_array_size() == 2);
    try {
        repo.repo_add_gene(new_gene2);
        assert(false);
    }
    catch (std::exception &e) {
        assert(true);
    }
    assert(repo.get_all_genes_from_repo().get_dynamic_array_size() == 2);
}
