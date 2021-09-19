//
// Created by VladB on 05-Apr-21.
//

#include <iostream>
#include "run_all_tests.h"
#include "repository_tests.h"
#include "service_tests.h"

void RunAllTests::run_all_tests() {
    std::cout << "===== RUNNING TESTS =====\n\n";
    RepositoryTests::run_all_repository_tests();
    ServiceTests::run_all_service_tests();
    std::cout << "===== TESTS DONE ===== \n\n";
}
