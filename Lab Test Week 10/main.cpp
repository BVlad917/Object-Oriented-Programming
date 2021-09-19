//
// Created by VladB on 05-Apr-21.
//

#include "persistency/repository.h"
#include "business/service.h"
#include "presentation/ui.h"
#include "tests/run_all_tests.h"

int main() {
    RunAllTests::run_all_tests();
    Repository repo;
    Service srv(repo);
    UI ui(srv);
    ui.start();
    return 0;
};