#include <iostream>
#include "Course.h"

Course::Course(std::string name){
    this-> courseName = name;
}
Course::Course(std::string name, std::string input){
    //?
}
Category* Course::getCategory(std::string categoryName){

    for(int i = 0; i < categories.size(); i++){
        if (categories[i] = categoryName){
            return categories[i];
        }

    }
    //what should this return if the category name does not exist??
}
std::vector<Category*> Course::getAllCategories(){
    //is the * supposed to be here?^^
    return this-> categories;
}
std::vector<Deliverable*> Course::getAllDeliverables(){
    //is the * supposed to be here?^^
    return this-> deliverables;
}

void Course::addDeliverable(Deliverable deliverable){
    //const Deliverable& deliverable -- would it be best to pass as constant reference since we are
    // just inserting to our deliverable vector?
    this-> deliverables.push_back(deliverable);
}
void Course::removeDeliverable(int index){
    if(index >= deliverables.size){
        return;
    }
    deliverables.erase(deliverables.begin() + index -1);
}