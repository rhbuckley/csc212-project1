#pragma once

#include "Category.h"

/** Default Constructor */
Category::Category(std::string name) : categoryName(name) {};


void Category::append(const Deliverable &deliverable) {
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

    // iterate & return memory address. we cannot
    // make this a : loop because it deals with memory
    for (int i = 0 ; i < deliverables.size() ; i++)
        rDeliverables.push_back(&deliverables[i]);

    // return the temp vector
    return rDeliverables;
}

double Category::getTotalPoints() {
    // define & set total to 0
    double total = 0;

    // iterate over vector and accumulate
    for (Deliverable deliverable : deliverables)
        total += deliverable.getGrade();

    // return total
    return total;
}

double Category::getPercentage() {
    // define & set total to 0
    double unweighted_percentage = 0;

    // iterate over vector and accumulate
    for (Deliverable deliverable : deliverables)
        unweighted_percentage += deliverable.getPercentage();

    // return unweighted percentage / num of assignments
    return unweighted_percentage / (double)deliverables.size();
}

std::vector<std::string> Category::serialize() {
    // define and initialize lines
    std::vector<std::string> lines;
    lines.push_back("BEGIN CATEGORY \"" + categoryName + "\"");

    // add deliverables to lines
    // we are nesting deliverables.serialize() because it has
    // no children
    for (Deliverable deliverable : deliverables)
        lines.push_back("   " + deliverable.serialize());

    // add ending line (using emplace back because of clion)
    lines.emplace_back("END CATEGORY");

    return lines;
}