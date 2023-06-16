//
// Created by Jack on 6/16/2023.
//
#include "Deliverable.h"
#include "Course.h"
#include "Student.h"
#include <iostream>
#include <fstream>
using namespace std;

int choose_functionality() {
    int option;
    cout << "Select an option by number: ";
    cout << "1) Add a student" << endl;
    cout << "2) Change student details" << endl;
    cout << "3) Get student grades" << endl;
    cout << "4) Quit program" << endl;
    cin >> option; cout << endl;
    while (option != 1 && option != 2 && option != 3 && option != 4) {
        cout << "Pick a valid number: ";
        cin >> option; cout << endl;
    }
    return option;
}

Student create_student_profile() {
    // Get student info
    string first_name, last_name;
    cout << "Enter first name: ";
    cin >> first_name; cout << endl;
    cout << "Enter last name: ";
    cin >> last_name; cout << endl;

    // Create student
    Student student = Student(first_name, last_name);

    // Vector for holding courses
    int num_courses;
    string course_name;

    // Get all their courses
    cout << "How many courses are you taking? ";
    cin >> num_courses; cout << endl;
    for (int i = 0; i < num_courses; i++) {
        cout << "Enter course name: ";
        cin >> course_name; cout << endl;
        student.addCourse(course_name);
    }

    return student;
}