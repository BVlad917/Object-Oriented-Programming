cmake_minimum_required(VERSION 3.19)
project(a10_BVlad917_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake")
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Charts)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Charts)

include_directories(business)
include_directories(domain)
include_directories(dynamic_array)
include_directories(errors)
include_directories(persistency)
include_directories(presentation)
include_directories(settings_handler)
include_directories(sqlite3)
include_directories(tests)
include_directories(utils)
include_directories(validation)

add_executable(a10_BVlad917_1
        business/service.cpp
        business/service.h
        domain/trench_coat.cpp
        domain/trench_coat.h
        dynamic_array/dynamic_array.cpp
        dynamic_array/dynamic_array.h
        dynamic_array/dynamic_vector.h
        errors/exceptions.h
        persistency/abstract_repository.h
        persistency/basket_csv_repo.cpp
        persistency/basket_csv_repo.h
        persistency/basket_file_repo.cpp
        persistency/basket_file_repo.h
        persistency/basket_html_repo.cpp
        persistency/basket_html_repo.h
        persistency/file_repo.cpp
        persistency/file_repo.h
        persistency/in_memory_repo.cpp
        persistency/in_memory_repo.h
        persistency/sql_repo.cpp
        persistency/sql_repo.h
        presentation/gui.cpp
        presentation/gui.h
        presentation/ui.cpp
        presentation/ui.h
        settings_handler/settings_handler.cpp
        settings_handler/settings_handler.h
        sqlite3/sqlite3.c
        sqlite3/sqlite3.h
        tests/all_tests.cpp
        tests/all_tests.h
        tests/domain_tests.cpp
        tests/domain_tests.h
        tests/dynamic_array_tests.cpp
        tests/dynamic_array_tests.h
        tests/exception_tests.cpp
        tests/exception_tests.h
        tests/repository_tests.cpp
        tests/repository_tests.h
        tests/service_tests.cpp
        tests/service_tests.h
        tests/templated_dynamic_vector_tests.cpp
        tests/templated_dynamic_vector_tests.h
        tests/validation_tests.cpp
        tests/validation_tests.h
        utils/abstract_filter.h
        utils/size_filter.h
        validation/trench_coat_validator.cpp
        validation/trench_coat_validator.h
        main.cpp actions/abstract_action.h actions/action_add.cpp actions/action_add.h actions/action_remove.cpp actions/action_remove.h actions/action_update.cpp actions/action_update.h qt_models_and_views/coats_table_model.cpp qt_models_and_views/coats_table_model.h qt_models_and_views/coats_widget.cpp qt_models_and_views/coats_widget.h qt_models_and_views/picture_delegate.cpp qt_models_and_views/picture_delegate.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
