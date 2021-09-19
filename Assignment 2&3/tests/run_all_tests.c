//
// Created by VladB on 07-Mar-21.
//

#include "run_all_tests.h"
#include "test_validators.h"
#include "test_dynamic_array.h"
#include "test_domain.h"
#include "test_repository.h"
#include "test_service.h"

void run_all_tests() {
    run_all_domain_tests();
    run_all_validators_tests();
    run_all_dynamic_array_tests();
    run_all_repo_tests();
    run_all_service_tests();
}