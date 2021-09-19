cmake_minimum_required(VERSION 3.17)
project(a45_BVlad917)

set(CMAKE_CXX_STANDARD 14)

add_executable(a45_BVlad917
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
        persistency/repository.cpp
        persistency/repository.h
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
        persistency/repeated_instances_repository.cpp
        persistency/repeated_instances_repository.h persistency/file_repository.cpp persistency/file_repository.h)
