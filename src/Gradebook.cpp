//
// Created by Richard Buckley on 6/24/23.
//

#include "Gradebook.h"
#include <iostream>

// Copy & Pasted from ./Deliverable.cpp
// This could be slightly more efficient. Not enough to rewrite
std::string betweenQuotes(std::string txt) {
    if (txt.find("\"") == std::string::npos) return txt;

    // find quotes
    int fq = txt.find_first_of('"');
    int lq = txt.find_last_of('"');

    // return substring
    return txt.substr(fq + 1, lq - fq - 1);
}

// we need to strip for spaces
std::string stripText(std::string txt) {
    while (txt[0] == ' ')
        txt = txt.substr(1, txt.size() - 1);
    return txt;
}

Gradebook::Gradebook(std::string fileName) {
    // open the file
    this->fileName = fileName;
    std::ifstream file(fileName);

    // could we open the file?
    if (!file.is_open())
        throw std::runtime_error("Could now find file, " + fileName);

    // now we can read the file
    std::string line, operation;

    // I am going to nest while loops to read in input here. This
    // might look high in time complexity, but it is (in my opinion
    // the best fast solution that is easy to read). The time complexity
    // will be O(n) regardless of loops

    // while there are lines to read...
    while (std::getline(file, line) && stripText(line) != "END GRADEBOOK") {
        // `line` = 'BEGIN GRADEBOOK'
        if (stripText(line).substr(0, 12) == "BEGIN COURSE") {
            // `line` = 'BEGIN COURSE "course name"

            // create a new course
            Course newCourse(betweenQuotes(line));

            // while we don't see 'END COURSE'
            while (std::getline(file, line) && stripText(line) != "END COURSE") {
                // when we see begin category - this might be redundant, but its just
                // using some consistency, which I like
                if (stripText(line).substr(0, 14) == "BEGIN CATEGORY") {
                    // `line` = 'BEGIN CATEGORY'

                    // create a new category
                    Category newCategory(betweenQuotes(line));

                    while (std::getline(file, line) && stripText(line).substr(0, 3) == "ADD") {
                        // `lin` = 'ADD DELIVERABLE "deliverable_name" 30 100
                        newCategory.append(Deliverable(stripText(line)));
                    } // end deliverable

                    newCourse.addCategory(newCategory);

                } // end category
            } // end course

            courses.push_back(newCourse);

            } // end course
        } // end gradebook

    // close the file
    file.close();
}


void Gradebook::appendCourse(Course course) {
    courses.push_back(course);
}

void Gradebook::removeCourse(Course *course) {
    // find course to remove
    for (int i = 0 ; i < courses.size() ; i++) {
        if (course != &courses[i]) continue;

        // if found swap element to delete to back
        for (int j = i ; j < courses.size() - 1 ; j++)
            std::swap(courses[j], courses[j  + 1]);

        // remove the course
        courses.pop_back();

        // return -> no memory addresses should be same
        return;
    }
}

std::vector<Course *> Gradebook::getCourses() {
    // define return list
    std::vector<Course *> rCourses;

    // iterate through list
    for (int i = 0 ; i < courses.size() ; i++)
        rCourses.push_back(&courses[i]);

    // return courses
    return rCourses;
}

void Gradebook::serialize() {
    // create a vector of lines
    std::vector<std::string> lines;
    lines.emplace_back("BEGIN GRADEBOOK");

    // apply indent to child lines
    for (Course course : courses)
        for (const std::string &line : course.serialize())
            lines.push_back("   " + line);

    // end gradebook
    lines.emplace_back("END GRADEBOOK");

    // save to a file
    std::ofstream file(fileName);

    // make sure we can open file
    if (!file.is_open())
        throw std::runtime_error("Could not open file " + fileName + "!");

    // write to output and file
    for (const std::string &line : lines) {
        file << line << std::endl;
//        std::cout << line << std::endl;
    }

    // close the file
    file.close();
}