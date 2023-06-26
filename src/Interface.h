#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Gradebook.h"

class Interface {
private:
    Gradebook gb;
    std::string path = "./.gradebook";  // overriden with custom path

    void displayWelcome();
    void saveFile() { gb.serialize(); };

    int drawMenuFromInput(const std::string &msg, std::vector<std::string> menu);
    void showClassView();
    void classCreationWiz();
    void classDeletionWiz();
    void displayCourseMenu(Course* course);

    void displayCourseCategories(Course* course);
    void categoryCreationWiz(Course* course);
    void categoryDeletionWiz(Course* course);

    void deliverableCreationWiz(Category *category);
    void displayCourseCategoryDeliverables(Category* category);
    void displayDeliverableDetails(Deliverable* deliverable, Category* category);

public:
    Interface();

    // this alias should help understand from main.cpp
    void startUserControl() { displayWelcome(); };
};
