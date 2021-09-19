//
// Created by VladB on 19-Mar-21.
//

#include <iostream>

#include "all_tests.h"
#include "domain_tests.h"
#include "dynamic_array_tests.h"
#include "repository_tests.h"
#include "validation_tests.h"
#include "service_tests.h"
#include "exception_tests.h"
#include "templated_dynamic_vector_tests.h"

void  AllTests::void_run_all_tests() {
    std::cout << "===== RUNNING TESTS =====\n";

    std::cout << "Running domain tests...\n";
    DomainTests::run_all_domain_tests();
    std::cout << "Domain tests done.\n";

    std::cout << "Running dynamic array tests...\n";
    DynamicArrayTests::run_all_dynamic_array_tests();
    std::cout << "Dynamic array tests done.\n";

    std::cout << "Running repository tests...\n";
    RepositoryTests::run_all_repo_tests();
    std::cout << "Repository tests done.\n";

    std::cout << "Running validation tests...\n";
    ValidationTests::run_all_validation_tests();
    std::cout << "Validation tests done.\n";

    std::cout << "Running service tests...\n";
    ServiceTests::run_all_service_tests();
    std::cout << "Service tests done.\n";

    std::cout << "Running exception tests...\n";
    ExceptionTests::run_all_exception_tests();
    std::cout << "Exception tests done.\n";

    std::cout << "Running Dynamic Vector (Template) tests...\n";
    TemplatedDynamicVectorTests::run_all_tdv_tests();
    std::cout << "Dynamic Vector (Template) tests done.\n";

    std::cout << "===== TESTS DONE =====\n";

}
