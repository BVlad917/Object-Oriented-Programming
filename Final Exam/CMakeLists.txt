cmake_minimum_required(VERSION 3.19)
project(e2_BVlad917)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake")
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Charts)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Charts)

include_directories(domain)

add_executable(e2_BVlad917
        domain/ethnologist.cpp
        domain/ethnologist.h
        main.cpp domain/building.cpp domain/building.h persistency/ethnologists_repo.cpp persistency/ethnologists_repo.h persistency/buildings_repo.cpp persistency/buildings_repo.h business/service.cpp business/service.h presentation/buildings_model.cpp presentation/buildings_model.h presentation/ethnologist_window.cpp presentation/ethnologist_window.h presentation/all_windows.cpp presentation/all_windows.h presentation/park_window.cpp presentation/park_window.h presentation/park_model.cpp presentation/park_model.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
