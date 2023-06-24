#pragma once

#include <string>
#include <vector>

#include "Deliverable.h"

class Category {
private:
    /** The name for the category */
    std::string categoryName;

    /** Pointer to Deliverables */
    std::vector<Deliverable> deliverables;

public:
    /** Default Constructor for Category */
    Category(std::string name);

    /** Name getter method */
    std::string getName() { return categoryName; };

    /** Add a deliverable to given category */
    void append(const Deliverable &deliverable);

    /** Remove a deliverable to a given category */
    void remove(Deliverable *deliverable);

    /** Get all Deliverables from Category */
    std::vector<Deliverable*> getDeliverables();

    /** Get Total Points for Category */
    double getTotalPoints();

    /** Get Total Percentage for Category */
    double getPercentage();

    /** Serialize */
    std::vector<std::string> serialize();
};