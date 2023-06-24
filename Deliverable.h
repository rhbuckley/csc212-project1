#pragma once

#include <string>
#include <sstream>


class Deliverable {
private:
    /** What is the identifying name of the deliverable? */
    std::string deliverableName;

    /** What Grade has the student gotten? */
    double grade;

    /** What is the grade out of? */
    double highestPossibleGrade;

public:
    /** Default Constructor */
    Deliverable(std::string name, double grade, double outOf);

    /** Serialization Functions */
    Deliverable(std::string fromString);
    std::string serialize();

    /** Add Grade */
    void setGrade(double grade);
    void setGrade(double grade, double outOf);

    /** Get Name */
    std::string getName() { return deliverableName; };

    /** Get Grade */
    double getGrade() { return grade; };

    /** Get Max Possible Points */
    double getMaxPts() { return highestPossibleGrade; };

    /** Get Percentage */
    double getPercentage() { return grade / highestPossibleGrade * 100; };
};