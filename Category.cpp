#pragma once

#include "Category.h"

/** Default Constructor */
Category::Category(std::string name) : categoryName(name) {};


void Category::append(Deliverable deliverable) {
    deliverables.push_back(deliverable);
}

void Category::remove(Deliverable *deliverable) {
    for (int i = 0 ; i < deliverables.size() ; i++) {
        // check if we found the deliverable to delete
        if (&deliverables[i] != deliverable) continue;

        // we need the deliverable that we want to delete to be at the
        // end of the vector
        // O(n^2) worst case
        for (unsigned int j = i ; j < deliverables.size() - 1 ; j++)
            std::swap(deliverables[j], deliverables[j + 1]);

        // now we a delete
        deliverables.pop_back();

        // return because no memory addresses should be the same
        return;
    }
}

std::vector<Deliverable *> Category::getDeliverables() {
    // need to iterate over deliverable vector and return pointers
    std::vector<Deliverable *> rDeliverables;

    // iterate & return memory addresses
    for (int i = 0 ; i < deliverables.size() ; i++)
        rDeliverables.push_back(&deliverables[i]);

    // return the temp vector
    return rDeliverables;
}

double Category::getTotalPoints() {
    // define & set total to 0
    double total = 0;

    // iterate over vector and accumulate
    for (int i = 0 ; i < deliverables.size() ; i++)
        total += deliverables[i].getGrade();

    // return total
    return total;
}

double Category::getPercentage() {
    // define & set total to 0
    double unweighted_percentage = 0;

    // iterate over vector and accumulate
    for (int i = 0 ; i < deliverables.size() ; i++)
        unweighted_percentage += deliverables[i].getPercentage();

    // return unweighted percentage / num of assignments
    return unweighted_percentage / (double)deliverables.size();
}