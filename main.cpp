//
// Created by Richard Buckley on 6/24/23.
//
#include "Gradebook.h"
#include <iostream>

int main() {
    Gradebook h("/Users/rhbuckley/Documents/College/CSC212/csc212-project1/.gradebook");
    std::vector<Course *> courses = h.getCourses();

    for (int i = 0 ; i < courses.size(); i++) {
        std::cout << "Course: " << courses[i]->getName() << std::endl;
        std::vector<Category *> categories = courses[i]->getAllCategories();

        for (int j = 0 ; j < categories.size() ; j++) {
            std::cout << "Category: " << categories[j]->getName() << std::endl;
            std::vector<Deliverable *> deliverables = categories[i]->getDeliverables();

            for (int k = 0 ; k < deliverables.size() ; k++) {
                std::cout << "Deliverable: " << deliverables[k]->getName();
                std::cout << " Score: " << deliverables[k]->getPercentage() << "%" << std::endl;
            }
        }
    }
}