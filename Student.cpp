//
// Created by Jack on 6/12/2023.
//
#include "Student.h"
using namespace std;

Student::Student(std::string first_name, std::string last_name) {
    this->firstName = first_name;
    this->lastName = last_name;
}

void Student::addDeliverable(Deliverable *deliverable, string course) {
    for (int i = 0; i < this->courses.size(); i++)  {
        if (this->courses[i]->getName() == course) {
            this->courses[i]->addDeliverable(deliverable);
            return;
        }
    }
}

void Student::removeDeliverable(Deliverable* deliverable, string course) {
    for (int i = 0; i < this->courses.size(); i++) {
        if (this->courses[i]->getName() == course) {
            this->courses[i]->removeDeliverable(deliverable);
            return;
        }
    }
}

void Student::addCourse(Course *course) {
    this->courses.push_back(course);
}

void Student::removeCourse(Course* course) {
    for (int i = 0; i < this->courses.size(); i++) {
        if (this->courses[i] == course) {
            this->courses.erase(this->courses.begin() + i - 1);
        }
    }
}

// This one still needs work, but I'm fried and taking a break
string Student::getAllSortedGrades(std::string course) {
    string all_cat_grades;
    // Get all the categories of the course
    vector<Category*> course_cats;
    for (int i = 0; i < this->courses.size(); i++) {
        if (this->courses[i]->getName() == course) {
            course_cats = this->courses[i]->getAllCategories();
            break;
        }
    }
    // For each category, get all deliverables
    vector<Deliverable*> cat_deliverables;
    string cat_total;
    for (int i = 0; i < course_cats.size(); i++) {
        // Add category name to final output
        cat_total += course_cats[i]->getName() + ": ";
        cat_deliverables = course_cats[i]->getDeliverables();
    }
}

string Student::getAllCategoryGrades(std::string course) {
    // Output string
    string category_sorted_grades; vector<Deliverable*> deliverables;
    for (int i = 0; i < this->courses.size(); i++) {
        Course* current_course = (this->courses[i]);
        // Search for the appropriate course
        if (current_course->getName() == course) {
            // For each category in the course
            for (int j = 0; j < current_course->getAllCategories().size(); j++) {
                Category* current_category = (current_course->getAllCategories()[j]);
                string category_info;
                // Get that category's deliverables' info
                deliverables = current_category->getDeliverables();
                for (int k = 0; k < deliverables.size(); k++) {
                    string name = deliverables[i]->getName();
                    string d_pts = std::to_string(deliverables[i]->getGrade());
                    string d_total = std::to_string(deliverables[i]->getMaxPts());
                    category_info += name + ": " + d_pts + "/"  + d_total  +  "\n";
                }
                category_sorted_grades += category_info;
            }
            string course_info = current_course->getGrade();
            category_sorted_grades += course_info;
            break;
        }
    }

    return category_sorted_grades;
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

string Student::getAssignmentGradesByCategory(std::string course, std::string category) {
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
    string courses_with_grades;
    for (int i = 0; i < this->courses.size(); i++) {
        string course_grade = courses[i]->getGrade();
        string course = courses[i]->getName();
        courses_with_grades += course + " grade: " + course_grade + "\n";
    }
    return courses_with_grades;
}