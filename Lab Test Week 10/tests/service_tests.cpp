//
// Created by VladB on 05-Apr-21.
//

#include <iostream>
#include <cassert>
#include "service_tests.h"
#include "../persistency/repository.h"
#include "../business/service.h"

void ServiceTests::test_add() {
    Repository repo;
    Service srv(repo);
    assert(srv.get_decreasing_genes().get_dynamic_array_size() == 0);
    srv.srv_add_gene("abc", "def", "seq1");
    assert(srv.get_decreasing_genes().get_dynamic_array_size() == 1);
    srv.srv_add_gene("abc", "xyz", "seq2");
    assert(srv.get_decreasing_genes().get_dynamic_array_size() == 2);
    try {
        srv.srv_add_gene("abc", "xyz", "seq3");
        assert(false);
    }
    catch (std::exception &e) {
        assert(true);
    }
    assert(srv.get_decreasing_genes().get_dynamic_array_size() == 2);
}

void ServiceTests::run_all_service_tests() {
    std::cout << "Running service tests...\n";
    ServiceTests::test_add();
    std::cout << "Service tests done.\n\n";
}
