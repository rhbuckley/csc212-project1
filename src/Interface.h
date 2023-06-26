#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Gradebook.h"

class Interface {
private:
    Gradebook gb;
    std::string path = "./.gradebook";  // overriden with custom path

    /** Entrypoint */
    void interface_entrypoint();

    /** Save gradebook */
    void save_gradebook() { gb.serialize(); };

    /** Generate a Menu and get input */
    int generate_menu_get_choice(const std::string &msg, std::vector<std::string> menu);

    /** View a Course Details */
    void course_view();

    /** View Course Actions, this is kind of a transition */
    void course_actions(Course* course);

    /** Create a Course */
    void course_create();

    /** Delete a course */
    void course_delete();

    /** view all categories */
    void categories_view(Course* course);

    /** Create a category */
    void categories_create(Course* course);

    /** Delete a Category */
    void categories_delete(Course* course);

    /** View All Deliverables & Percentages */
    void deliverable_view(Category* category);

    /** Create a Deliverable */
    void deliverable_create(Category *category);

    /** This will include Edit & Delete sub-methods */
    void deliverable_actions(Deliverable* deliverable, Category* category);

public:
    Interface();

    // this alias should help understand from main.cpp
    void startUserControl() { interface_entrypoint(); };
};
