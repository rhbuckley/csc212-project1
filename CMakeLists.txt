cmake_minimum_required(VERSION 3.24)
project(csc212_project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(csc212_project1
        # Category
        Category.cpp
        Category.h

        # Course
        Course.cpp
        Course.h

        # Deliverable
        Deliverable.cpp
        Deliverable.h

        # Gradebook
        Gradebook.cpp
        Gradebook.h
        
        # Main
        main.cpp
        interface.cpp interface.h)
