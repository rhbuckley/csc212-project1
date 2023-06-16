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

void Student::removeDeliverable(int index) {
    deliverables.erase(deliverables.begin() + index - 1);
}

void Student::addCourse(Course *course) {
    courses.push_back(course);
}

void Student::removeCourse(int index) {
    courses.erase(courses.begin() + index - 1);
}

double Student::getAverageGrade() {
    double total_grade = 0;
    for (int i = 0; i < deliverables.size(); i++) {
        total_grade += deliverables[i]->getGrade();
    }
    double average_grade = total_grade / deliverables.size();
    return average_grade;
}

vector<double> Student::getGradesByCourse(Course *course) {

}