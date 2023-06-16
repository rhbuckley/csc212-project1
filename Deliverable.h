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

    /** What Grades has the student gotten? */
    double grade;

    /** What is the grade out of? */
    double highestPossibleGrade;

public:
    /** Default Constructor */
    Deliverable(std::string name, Category* category);
    Deliverable(std::string name, Category* category, double grade, double out_of);

    /** Add Grade */
    void setGrade(double grade);

    /** Get Name */
    string getName();

    /** Get Grade */
    double getGrade();

    /** Get Max Possible Points */
    double getMaxPts();

    /** Get Percentage */
    double getPercentage();
};