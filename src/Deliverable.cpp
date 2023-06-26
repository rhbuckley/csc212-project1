//
// Created by Richard Buckley on 6/21/23.
//

#include "Deliverable.h"

// This could be slightly more efficient. Not enough to rewrite
std::string stripQuotes(std::string &txt) {
    if (txt.find("\"") == std::string::npos) return txt;

    txt.replace(txt.find("\""), 1, "'");
    return stripQuotes(txt);
}

Deliverable::Deliverable(std::string name, double grade, double outOf) {
    // We will be using double quotes in save file. Let's convert
    // any double quotes ("") to single quotes ('')
    this->deliverableName = stripQuotes(name);
    this->grade = grade;
    this->highestPossibleGrade = outOf;
}

void Deliverable::setGrade(double newGrade) {
    this->grade = newGrade;
}

void Deliverable::setGrade(double newGrade, double outOf) {
    this->grade = newGrade;
    this->highestPossibleGrade = outOf;
}

std::string Deliverable::serialize() {
    return "ADD DELIVERABLE \"" + deliverableName + "\" " + std::to_string(grade) + " " + std::to_string(highestPossibleGrade);
}

Deliverable::Deliverable(std::string fromString) {
    // Find the First & Last Quotes and assemble a string
    unsigned int fq = fromString.find_first_of("\"");
    unsigned int lq = fromString.find_last_of("\"");
    std::string a_name = fromString.substr(fq + 1, lq - fq - 1);

    // Use the last quote to find out where to start searching for
    // the a_grade and a_out_of
    // Find First Space after Last Quote

    // add 2 to account for `" `
    int spaceAfterGrade = fromString.substr(lq + 2, fromString.size()).find(' ');
    std::string a_grade = fromString.substr(lq + 2, spaceAfterGrade);

    // add 1 to account for `40 `
    int spaceBeforeOutOf = fromString.find_last_of(' ');
    std::string a_out_of = fromString.substr(spaceBeforeOutOf, fromString.size() - spaceBeforeOutOf);

    // Now we can just update the values in the deliverable
    this->deliverableName = a_name;
    this->grade = std::stod(a_grade);
    this->highestPossibleGrade = std::stod(a_out_of);
}