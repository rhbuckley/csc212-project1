#pragma once

#include <string>
#include <vector>

#include "Deliverable.h"
#include "Course.h"


/** Student Class for Scheduling Project */
class Student {
    private:
        /** Student Information */
        std::string firstName;
        std::string lastName; 

        /** Pointer to Courses taken */
        std::vector<Course*> courses;

        /** Pointer to Deliverables */
        std::vector<Deliverable*> deliverables;

    public:
        /** Default Constructor */
        Student(std::string first_name, std::string last_name);

        /** Add Deliverable to Student */
        void addDeliverable(Deliverable *deliverable);

        /** Remove Deliverable from Student */
        void removeDeliverable(int index);

        /** Add Course for Student */
        void addCourse(Course *course);

        /** Remove Course from Student */
        void removeCourse(int index);

        /** Get Average Grade */
        double getAverageGrade();

        /** Get Grades by Course */
        std::vector<double> getGradesByCourse(Course *course);
};