cmake_minimum_required(VERSION 3.17)
project(a67_BVlad917)

set(CMAKE_CXX_STANDARD 14)

add_executable(a67_BVlad917
        main.cpp
        domain/trench_coat.cpp
        domain/trench_coat.h
        tests/domain_tests.cpp
        tests/domain_tests.h
        tests/all_tests.cpp
        tests/all_tests.h
        dynamic_array/dynamic_array.cpp
        dynamic_array/dynamic_array.h
        tests/dynamic_array_tests.cpp
        tests/dynamic_array_tests.h
        errors/exceptions.h
        tests/repository_tests.cpp
        tests/repository_tests.h
        validation/trench_coat_validator.cpp
        validation/trench_coat_validator.h
        tests/validation_tests.cpp
        tests/validation_tests.h
        business/service.cpp
        business/service.h
        tests/service_tests.cpp
        tests/service_tests.h
        presentation/ui.cpp
        presentation/ui.h
        tests/exception_tests.cpp
        tests/exception_tests.h
        dynamic_array/dynamic_vector.h
        tests/templated_dynamic_vector_tests.cpp
        tests/templated_dynamic_vector_tests.h
        utils/abstract_filter.h utils/size_filter.h
        persistency/abstract_repository.h
        persistency/in_memory_repo.cpp
        persistency/in_memory_repo.h
        persistency/file_repo.cpp
        persistency/file_repo.h
        persistency/basket_file_repo.cpp
        persistency/basket_file_repo.h
        persistency/basket_csv_repo.cpp
        persistency/basket_csv_repo.h
        persistency/basket_html_repo.cpp
        persistency/basket_html_repo.h
        persistency/sql_repo.cpp
        persistency/sql_repo.h
        sqlite3/sqlite3.h
        sqlite3/sqlite3.c)
