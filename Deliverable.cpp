#include "Deliverable.h"
#include "Category.h"
#include <vector>
#include <string>

/** Default Constructor */
Deliverable::Deliverable(std::string name, Category* category){
    this->deliverableName = name;
    this->category = category;
    this->grade = 0;
    this->highestPossibleGrade = 0;
}

Deliverable::Deliverable(std::string name, Category* category, double grade, double out_of){
    this->deliverableName = name;
    this->category = category;
    this->grade = grade;
    this->highestPossibleGrade = out_of;
}

/** Add Grade */
void Deliverable::setGrade(double grade, double out_of){
    this->grade = grade;
    this->highestPossibleGrade = out_of;
}

/** Get Grade */
double Deliverable::getGrade(){
    return this->grade;
}

/** Get Percentage */
double Deliverable::getPercentage(){
    return 100 * (this->grade / this->highestPossibleGrade);
}