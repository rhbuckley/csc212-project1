#pragma once

#include <string>
#include <vector>

#include "Category.h"
#include "Grade.h"


class Deliverable {
    private:
        /** What kind of deliverable is this? */
        Category* category;

        /** What is the identifying name of the deliverable? */
        std::string deliverableName;

        /** What Grades have students gotten? */
        std::vector<Grade> grades;

    public:
        /** Default Constructor */
        Deliverable(std::string name, Category* category);

        /** Add Grade */
        void addGrade(Grade grade);

        /** Remove Grade */
        void removeGrade(int index);

        /** Get Grades */
        std::vector<Grade*> getGrades();

        /** Get Average Grade */
        double getAverageGrade();
};