#pragma once

#include <string>
#include <vector>

// This is a rough patch for me because I know that there is a circular
// import going on between Category & Deliverable, however, if we do not
// have this circular import, if we entry to grades via student, we will
// not be able to figure out what Category a deliverable belongs to without
// going from student to deliverable from deliverable to course from course
// to categories from categories to deliverable. It is complicated, and I 
// think we should try to find a better way
class Deliverable;  // this will be overwritten

class Category {
    private:
        /** The name for the category */
        std::string categoryName;

        /** Pointer to Deliverables */
        std::vector<Deliverable*> deliverables;

    public:
        /** Default Constructor for Category */
        Category(std::string name);

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