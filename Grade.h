#pragma once

#include "Student.h"
#include "Deliverable.h"

class Grade {
    private:
        /** The Grade Received */
        double grade;

        /** The Deliverable the grade belongs to */
        Deliverable* deliverable;

        /** The Student the Grade Belongs to */
        Student* student;
    
    public:
        /** Default Constructor */
        Grade(double score, Deliverable* deliverable, Student* student);

        /** Get Grade */
        double get();

        /** Update Grade */
        void update(double new_score);
};