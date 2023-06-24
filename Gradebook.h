#pragma once

#include "Course.h"


#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>

class Gradebook {
    private:
        std::vector<Course> courses;

    public:
        /** Just Create a Gradebook instance */
        Gradebook() {}

        /** Create a gradebook instance from a file */
        Gradebook(std::string fileName);

        /** Add a course to the gradebook */
        void appendCourse(Course &course);

        /** Remove a course from the gradebook */
        void removeCourse(Course* course);

        /** Get all courses in the gradebook */
        std::vector<Course*> getCourses();
};