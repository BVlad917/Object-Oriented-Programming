cmake_minimum_required(VERSION 3.19)
project(t2_BVlad917_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(t2_BVlad917_1
        main.cpp domain/measurement.cpp domain/measurement.h domain/bmi.cpp domain/bmi.h domain/bp.cpp domain/bp.h persistency/person.cpp persistency/person.h presentation/ui.cpp presentation/ui.h business/service.cpp business/service.h)
