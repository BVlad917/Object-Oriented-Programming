cmake_minimum_required(VERSION 3.17)
project(a23-BVlad917)

set(CMAKE_C_STANDARD 99)

add_executable(a23-BVlad917
        domain/date.c
        domain/date.h
        main.c domain/product.c
        domain/product.h
        validation/date_validator.c
        validation/date_validator.h
        validation/product_validator.c
        validation/product_validator.h
        dynamic_array/dynamic_array.c
        dynamic_array/dynamic_array.h
        persistency/repository.c
        persistency/repository.h
        tests/test_domain.c
        tests/test_domain.h
        tests/test_dynamic_array.c
        tests/test_dynamic_array.h
        tests/test_validators.c
        tests/test_validators.h
        tests/run_all_tests.c
        tests/run_all_tests.h
        tests/test_repository.c
        tests/test_repository.h
        business/service.c
        business/service.h
        tests/test_service.c
        tests/test_service.h
        presentation/ui.c
        presentation/ui.h validation/category_validator.c validation/category_validator.h utils/comparators_and_filters.c utils/comparators_and_filters.h undo_redo_inv_ops/inv_ops_undo_redo.c undo_redo_inv_ops/inv_ops_undo_redo.h)