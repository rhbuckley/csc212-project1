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

    int drawMenuFromInput(std::string msg, std::vector<std::string> menu);
    void showClassView();
    void classCreationWiz();
    void classDeletionWiz();
    void displayCourseMenu(Course* course);

    void displayCourseCategories();
    void categoryCreationWiz();
    void categoryDeletionWiz();

    void displayCourseCategoryDeliverables();
    void deliverableCreationWiz();
    void deliverableDeletionWiz();
    

public:
    Interface();

    // this alias should help understand from main.cpp
    void startUserControl() { displayWelcome(); };
};