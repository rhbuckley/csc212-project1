//
// Created by Richard Buckley on 6/21/23.
//

#include "Course.h"

/** Default Constructor **/
Course::Course(std::string name) : courseName(name) {};

Category *Course::findCategory(std::string categoryName) {
    // iterate over categories vector
    for (int i = 0 ; i < categories.size() ; i++)
        // if the category names match...
        if (categories[i].getName() == categoryName)
            // return the category address
            return &categories[i];

    // return nullptr if nothing is found
    return nullptr;
}

std::vector<Category *> Course::getAllCategories() {
    // define temp categories
    std::vector<Category *> rCategories;

    // iterate through categories
    for (int i = 0 ; i < categories.size() ; i++)
        rCategories.push_back(&categories[i]);

    // return temp categories
    return rCategories;
}

std::vector<Deliverable *> Course::getAllDeliverables() {
    // define temp deliverables
    std::vector<Deliverable *> rDeliverables;

    // iterate through categories
    for (int i = 0 ; i < categories.size() ; i++) {
        std::vector<Deliverable *> localDeliverables = categories[i].getDeliverables();
        rDeliverables.insert(rDeliverables.end(), localDeliverables.begin(), localDeliverables.end());
    }

    // return the new vector
    return rDeliverables;
}

void Course::addCategory(Category category) {
    categories.push_back(category);
}

void Course::removeCategory(Category *category) {
    // iterate over vector of categories
    for (int i = 0 ; i < categories.size() ; i++) {
        if (&categories[i] != category) continue;

        // push focused element to end of vector
        for (int j = i ; j < categories.size() - 1 ; j++)
            std::swap(categories[j], categories[j + 1]);

        // remove from vector
        categories.pop_back();

        return;
    }
}

std::string Course::getGrade() {
    // get weighted percentage
    double weighted_percent = getPercentage();

    // determine the grade
    if (weighted_percent >= 94) return "A";
    if (weighted_percent >= 90) return "A-";
    if (weighted_percent >= 87) return "B+";
    if (weighted_percent >= 83) return "B";
    if (weighted_percent >= 80) return "B-";
    if (weighted_percent >= 77) return "C+";
    if (weighted_percent >= 73) return "C";
    if (weighted_percent >= 70) return "C-";
    if (weighted_percent >= 67) return "D+";
    if (weighted_percent >= 60) return "D";
    return "F";
}

double Course::getPercentage() {
    double unweighted_percent = 0;

    // get all category percentages
    for (int i = 0 ; i < categories.size() ; i++)
        unweighted_percent += categories[i].getPercentage();

    // weight the category
    return unweighted_percent / (double)categories.size();
}

std::vector<std::string> Course::serialize() {
    // create vector
    std::vector<std::string> lines;
    lines.push_back("BEGIN COURSE \"" + courseName + "\"");

    // again, the const & was clang tidy
    for (Category category : categories)
        for (const std::string &line : category.serialize())
            lines.push_back("   " + line);

    // ending line
    lines.emplace_back("END COURSE");
    return lines;
}