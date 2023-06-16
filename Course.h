#pragma once

#include <string>
#include <vector>

#include "Deliverable.h"

// Again, there is a bit of circular importing going on around here to maintain
// these complex relationships, but what are you going to do. This declaration
// is just temporary and will be overwritten in Deliverable.h > Category.h
class Category;


class Course {
    private:
        /** The name for the course */
        std::string courseName;

        /** A vector containing the deliverables for the course */
        std::vector<Deliverable*> deliverables;

        /** A vector containing the categories of deliverables */
        std::vector<Category> categories;

    public:
        /** Parameterized Constructor */
        Course(std::string name);

        /** Parse from String */
        Course(std::string name, std::string input);

        std::string getName();

        /** Get Category */
        Category* getCategory(std::string categoryName);

        /** Get all Categories */
        std::vector<Category*> getAllCategories();

        /** Get Deliverables */
        std::vector<Deliverable*> getAllDeliverables();

        /** Add Deliverable */
        void addDeliverable(Deliverable* deliverable);

        /** Remove Deliverable */
        void removeDeliverable(Deliverable* deliverable);

        /** Get grade for the course */
        string getGrade();

        /** Get grades for one category */
        string getCategoryGrades(string category);
};
