cmake_minimum_required(VERSION 3.17)
project(t1_BVlad917_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(t1_BVlad917_1
        main.cpp dynamic_vector/dynamic_vector.cpp dynamic_vector/dynamic_vector.h domain/gene.cpp domain/gene.h persistency/repository.cpp persistency/repository.h business/service.cpp business/service.h presentation/ui.cpp presentation/ui.h tests/service_tests.cpp tests/service_tests.h tests/repository_tests.cpp tests/repository_tests.h tests/run_all_tests.cpp tests/run_all_tests.h)
