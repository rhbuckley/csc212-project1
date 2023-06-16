cmake_minimum_required(VERSION 3.25)
project(csc212_project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(csc212_project1
        Category.cpp
        Category.h
        Course.h
        Deliverable.cpp
        Deliverable.h
        Grade.h
        Student.h Student.cpp Course.cpp Interface.cpp main.cpp)
