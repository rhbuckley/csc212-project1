#include "Category.h"
#include "Deliverable.h"

#include <algorithm>

/** Default Category Constructor -> Gets & Sets a name for Category */
Category::Category(std::string name) : categoryName(name) {}

/** Adds a Deliverable to the Category */
void Category::append(Deliverable *deliverable) {
    deliverables.push_back(deliverable);
};


/** Removes a Deliverable from the Category */
void Category::remove(Deliverable *deliverable) {
    // Get Iterator Pointing to Deliverabe
    auto it = std::find(deliverables.begin(), deliverables.end(), deliverable);

    // If Element was Found...
    if (it != deliverables.end()) {
        
        // Swap the Iterator of it with the end of the deliverables
        // using this because I chose to use std::find, which returns
        // an iterator...
        std::iter_swap(it, deliverables.end());

        // Remove the Last Element (we just swapped the iterator to the back :0)
        deliverables.pop_back();
    }
}


/** Get all Deliverables in a given Category */
std::vector<Deliverable*> Category::getDeliverables() {
    return deliverables;
}

/** Get Total Points for Category */
double Category::getTotalPoints() {
    double total = 0;

    for (auto it = deliverables.begin() ; it != deliverables.end() ; ++it)
        total += (*it)->getGrade();

    return total;
}

/** Get Average Percentage for Category */
double Category::getPercentage() {
    double total = 0;

    for (auto it = deliverables.begin() ; it != deliverables.end() ; ++it)
        total += (*it)->getPercentage();

    return total / (double)deliverables.size();
}