#include <iostream>
#include "Course.h"

Course::Course(std::string name){
    this-> courseName = name;
}
Course::Course(std::string name, std::string input){
    //?
}

string Course::getName() {
    return this->courseName;
}

Category* Course::getCategory(std::string categoryName){
    for(int i = 0; i < categories.size(); i++){
        if (categories[i].categoryName = categoryName){
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

string Course::getGrade() {
    double total_points = 0;
    double earned_points = 0;
    for (int i = 0; i < deliverables.size(); i++) {
        double total_del_pts = deliverables[i].getMaxPts();
        double earned_del_pts = deliverables[i].getGrade();
        total_points += total_del_pts;
        earned_points += earned_del_pts;
    }
    double course_grade = (100 * (earned_points / total_points));
    return std::to_string(course_grade);
}

string Course::getCategoryGrades(std::string category) {
    // All individual assignment info
    string ind_category_grades;
    // Totals within the category
    double cat_earned_pts;
    double cat_total_pts;
    for (int i = 0; i < deliverables.size(); i++) {
        // Create a line with name and score/total, add score and total to category sums
        string d_name = deliverables[i].getName();
        cat_earned_pts = deliverables[i].getGrade();
        cat_total_pts = deliverables[i].getMaxPts();
        string d_grade = std::to_string(deliverables[i].getGrade());
        string d_total = std::to_string(deliverables[i].getMaxPts());
        string line = d_name + ": " + d_grade + "/" + d_total + "\n";
        ind_category_grades += line;
    }
    // Create final string with assignment grades and total category grade
    string final_earned = std::to_string(cat_earned_pts);
    string final_total = std::to_string(cat_total_pts);
    string cat_totals = category + ": " + final_earned + "/" + final_total + "\n";
    string all_category_info = ind_category_grades + cat_totals;
    return all_category_info;
}