#pragma once

#include <string>
#include <vector>

// https://stackoverflow.com/questions/4816698/avoiding-circular-dependencies-of-header-files
// this is a forward declaration and will be overwritten
class Deliverable;  

class Category {
    private:
        /** The name for the category */
        std::string categoryName;

        /** Pointer to Deliverables */
        std::vector<Deliverable*> deliverables;

    public:
        /** Default Constructor for Category */
        Category(std::string name);

        /** Name getter method */
        std::string getName();

        /** Add a deliverable to given category */
        void append(Deliverable *deliverable);

        /** Remove a deliverable to a given category */
        void remove(Deliverable *deliverable);

        /** Get all Deliverables from Category */
        std::vector<Deliverable*> getDeliverables();

        /** Get Total Points for Category */
        double getTotalPoints();

        /** Get Total Percentage for Category */
        double getPercentage();

};