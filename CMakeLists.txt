cmake_minimum_required(VERSION 3.24)
project(csc212_project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(csc212_project1
        # Category
        src/Category.cpp
        src/Category.h

        # Course
        src/Course.cpp
        src/Course.h

        # Deliverable
        src/Deliverable.cpp
        src/Deliverable.h

        # Gradebook
        src/Gradebook.cpp
        src/Gradebook.h

        # Interface
        src/Interface.cpp
        src/Interface.h

        # Main
        src/main.cpp
        )
