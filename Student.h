#pragma once

#include <string>
#include <vector>
using namespace std;

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
        void addDeliverable(Deliverable *deliverable, string course);

        /** Remove Deliverable from Student */
        void removeDeliverable(Deliverable* deliverable, string course);

        /** Add Course for Student */
        void addCourse(Course *course);

        /** Remove Course from Student */
        void removeCourse(Course* course);

        /** Gets all assignment grades for given course */
        string getAllSortedGrades(string course);

        /** Gets all category totals for given course */
        string getCategorySortedGrades(string course);

        /** Gets total grade of given course */
        string getGradeByCourse(string course);

        /** Gets all grades of one category in given course */
        string getGradeByCategory(string course, string category);

        /** Gets all grades of all courses */
        string getAllGrades();
};