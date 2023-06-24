#pragma once

#include <string>
#include <vector>

#include "Deliverable.h"
#include "Category.h"

class Course {
private:
    /** The name for the course */
    std::string courseName;

    /** A vector containing the categories of deliverables */
    std::vector<Category> categories;

public:
    /** Parameterized Constructor */
    Course(std::string name);

    std::string getName() { return courseName; };

    /** Get Category */
    Category* findCategory(std::string categoryName);

    /** Get all Categories */
    std::vector<Category*> getAllCategories();

    /** Get Deliverables */
    std::vector<Deliverable*> getAllDeliverables();

    /** Add Category */
    void addCategory(Category category);

    /** Remove Category */
    void removeCategory(Category *category);

    /** Get grade for the course */
    std::string getGrade();

    /** Get percentage for the course */
    double getPercentage();
};
