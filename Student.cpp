//
// Created by Jack on 6/12/2023.
//
#include "Student.h"
using namespace std;

Student::Student(std::string first_name, std::string last_name) {
    this->firstName = first_name;
    this->lastName = last_name;
}

void Student::addDeliverable(Deliverable *deliverable) {
    deliverables.push_back(deliverable);
}

void Student::removeDeliverable(Deliverable* deliverable) {
    for (int i = 0; i < this->deliverables.size(); i++) {
        if (this->deliverables[i] == deliverable) {
            this->deliverables.erase(this->deliverables.begin() + i - 1);
        }
    }
}

void Student::addCourse(Course *course) {
    courses.push_back(course);
}

void Student::removeCourse(Course* course) {
    for (int i = 0; i < this->courses.size(); i++) {
        if (this->courses[i] == course) {
            this->courses.erase(this->courses.begin() + i - 1);
        }
    }
}

string Student::getAllSortedGrades(std::string course) {

}

string Student::getCategorySortedGrades(std::string course) {

}

string Student::getGradeByCourse(std::string course) {
    string course_info = course + ": ";
    for (int i = 0; i < this->courses.size(); i++) {
        if (this->courses[i]->getName() == course) {
            course_info += this->courses[i]->getGrade();
        }
        break;
    }
    return course_info;
}

string Student::getGradeByCategory(std::string course, std::string category) {
    string all_category_info;
    for (int i = 0; i < this->courses.size(); i++) {
        if (this->courses[i]->getName() == course) {
            all_category_info = this->courses[i]->getCategoryGrades(category);
        }
        break;
    }
    return all_category_info;
}

string Student::getAllGrades() {

}