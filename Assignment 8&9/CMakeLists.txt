cmake_minimum_required(VERSION 3.17)
project(a67_BVlad917)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake")
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Charts)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Charts)

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
        sqlite3/sqlite3.c presentation/gui.cpp presentation/gui.h settings_handler/settings_handler.cpp settings_handler/settings_handler.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
