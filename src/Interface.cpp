//
// Created by Richard Buckley on 6/25/23.
//

#include "Interface.h"

Interface::Interface() {
    std::cout << "Welcome to Gradebook. A CSC 211 project by Richard, Nathaniel, Jack & Monet" << std::endl;

    // early check for autosave
    std::ifstream file(path);
    if (file.is_open()) {
        std::cout << "Auto saved File Found, using last version" << std::endl;
        std::cout << "File found at ./.gradebook" << std::endl;
        gb = Gradebook(path);
        return;
    }

    // we could not find an autosave
    char saved = 'z';  // placeholder for c-tidy

    // basically while we don't know if we have a file or not, do nothing
    while (saved != 'Y' && saved != 'N') {
        std::cout << "Do you have a save file already? (Y / N)" << std::endl;
        std::cin >> saved;

        // convert to upper-case for parsing
        if (saved >= 'a') saved -= 'a' - 'A';
    }

    // if there is a save file, use the old gradebook, if not...overwrite
    if (saved == 'Y') {
        // check local directory first for save file
        std::cout << "Please Enter the Absolute Path to Your Save File..." << std::endl;
        std::cin >> path;

        gb = Gradebook(path);
    } else {
        // ok no save file
        std::cout << "Starting New Session, Your Changes will be auto saved to .gradebook" << std::endl;

        gb = Gradebook();
    }
}

int Interface::generate_menu_get_choice(const std::string &msg, std::vector<std::string> menu) {
    // Draw Beginning Line
    for (int i = 0 ; i < 30 ; i++) std::cout << "-";
    std::cout << std::endl;

    std::cout << msg << std::endl;

    // Write Selections
    for (int i = 1 ; i <= menu.size() ; i++ )
        std::cout << "  [" << i << "] -- " << menu[i - 1] << std::endl;

    // Draw Ending Line
    for (int i = 0 ; i < 30 ; i++) std::cout << "-";
    std::cout << std::endl;

    // Get Input
    std::cout << "? ";

    // Get Choice
    std::string rawChoice;
    std::cin >> rawChoice;

    // convert like this to handle a char being entered
    try {
        int choice = std::stoi(rawChoice);
        // Validate Choice
        if (choice > menu.size() || choice <= 0) {
            std::cout << "Invalid Selection" << std::endl;
            return generate_menu_get_choice(msg, menu);
        }

        // Return choice
        return choice;
    } catch (const std::exception &e) {
        std::cout << "Invalid Selection" << std::endl;
        return generate_menu_get_choice(msg, menu);
    }

}

void Interface::interface_entrypoint() {
    std::vector<std::string> menu = {
            "View Classes",
            "Add a Class",
            "Delete a Class",
            "Exit"
    };

    int choice = 0;  // placeholder
    while (choice <= 0 || choice > menu.size())
        choice = generate_menu_get_choice("Welcome", menu);

    if (choice == 1) return course_view();
    if (choice == 2) return course_create();
    if (choice == 3) return course_delete();
}

void Interface::course_view() {
    std::vector<Course*> courses = gb.getCourses();
    std::vector<std::string> courseNames;

    if (courses.size() == 0) {
        std::cout << "You aren't registered in any courses" << std::endl;
        return interface_entrypoint();
    }

    for (Course *course : courses) {
        std::string temp;

        temp = course->getName();
        temp += " - ";

        if (!course->getAllDeliverables().empty())
            temp += std::to_string((int)course->getPercentage()) + "%";
        else
            temp += "NA";

        courseNames.push_back(temp);
    }

    courseNames.emplace_back("Exit");

    int choice = generate_menu_get_choice("Select a Course to Proceed", courseNames);
    if (choice != courseNames.size()) return course_actions(courses[choice - 1]);

    // go back to main menu
    return interface_entrypoint();
}

void Interface::course_create() {
    std::string className;

    std::cout << "Enter Class Name for this course" << std::endl;

    // the name isn't a key so though I don't know why a user may want
    // to name their classes the same, they can
    std::cout << "? ";
    std::cin.ignore();
    std::getline(std::cin, className);

    gb.appendCourse(Course(className));
    // we made a change, save it
    save_gradebook();

    // go back to main menu
    return interface_entrypoint();
}

void Interface::course_delete() {
    std::vector<Course*> courses = gb.getCourses();
    std::vector<std::string> courseNames;

    if (courses.empty()) {
        std::cout << "You aren't registered in any courses" << std::endl;
        return interface_entrypoint();
    }

    for (Course *course : courses)
        courseNames.push_back(course->getName());

    courseNames.emplace_back("Cancel");

    int choice = generate_menu_get_choice("Select a Course to Delete", courseNames);

    if (choice != courseNames.size()) {
        gb.removeCourse(courses[choice - 1]);
        save_gradebook();
        std::cout << "Saved" << std::endl;
    }
    return interface_entrypoint();
}

void Interface::course_actions(Course *course) {
    std::vector<std::string> choices = {
            "View Assignment Categories",
            "Add Assignment Category",
            "Delete Assignment Category",
            "Home"
    };

    int choice = generate_menu_get_choice("Select an Option to Proceed", choices);

    if (choice == 1) return categories_view(course);
    if (choice == 2) return categories_create(course);
    if (choice == 3) return categories_delete(course);

    if (choice == 4) return interface_entrypoint();
}

void Interface::categories_view(Course *course){
    std::vector<std::string> choices;

    for (Category *category : course->getAllCategories())
        choices.push_back(category->getName());

    if (choices.empty()) {
        std::cout << "There are no available categories!" << std::endl;
        return course_actions(course);
    }

    choices.emplace_back("Go Back");

    int choice = generate_menu_get_choice("Select a Category to Proceed", choices);

    if (choice == choices.size()) return course_actions(course);
    return deliverable_view(course->getAllCategories()[choice - 1]);
}

void Interface::categories_create(Course* course) {
    std::string cat_name;
    std::cout << "Enter name for new category" << std::endl;
    std::cout << "? ";
    std::cin.ignore();
    std::getline(std::cin, cat_name);

    course->addCategory(Category(cat_name));
    save_gradebook();
    return categories_view(course);
}

void Interface::categories_delete(Course* course) {
    std::vector<std::string> choices;

    for (Category *category : course->getAllCategories())
        choices.push_back(category->getName());

    choices.emplace_back("Go Back");

    int choice = generate_menu_get_choice("Delete a Category", choices);
    if (choice == choices.size() + 1) return categories_view(course);

    course->removeCategory(course->getAllCategories()[choice - 1]);
    save_gradebook();
    return categories_view(course);
}

void Interface::deliverable_view(Category* category){
    std::vector<std::string> choices;

    for (Deliverable *deliverable : category->getDeliverables())
        choices.push_back(deliverable->getName() + " " + std::to_string((int)deliverable->getPercentage()) + "%");

    choices.emplace_back("Add New Deliverable");
    choices.emplace_back("Go Home");

    int choice = generate_menu_get_choice("Select a Deliverable to Edit or Delete", choices);

    if (choice == choices.size() - 1) return deliverable_create(category);
    if (choice == choices.size()) return interface_entrypoint();
    return deliverable_actions(category->getDeliverables()[choice - 1], category);
}

void Interface::deliverable_create(Category *category) {
    std::cout << "Enter a name for the deliverable" << std::endl;
    std::cout << "? ";
    std::string input;
    std::cin.ignore();
    std::getline(std::cin, input);

    double score, maxScore;
    std::cout << "Enter Your Score and Maximum Possible Score. (e.g. 80 100 would be equivalent to 80%)" << std::endl;
    std::cin >> score >> maxScore;

    category->append(Deliverable(input, score, maxScore));
    save_gradebook();
    return deliverable_view(category);
}

void Interface::deliverable_actions(Deliverable* deliverable, Category* category) {
    std::vector<std::string> choices = {
        "Edit",
        "Delete",
        "Back",
    };

    std::cout << "Deliverable: " << deliverable->getName() << std::endl;
    std::cout << "Scored: " << deliverable->getGrade() << " / " << deliverable->getMaxPts() << std::endl;

    int choice = generate_menu_get_choice("Select Action", choices);

    // Edit
    if (choice == 1) {
        int grade = -1, outOf = -1;

        // todo: add input validation so a char doesn't crash
        while (grade < 0 && outOf < 0) {
            std::cout << "Please Enter your New Grade SPACE Out Of Many Points. e.g. (80 100) which would be 80%" << std::endl;
            std::cin >> grade >> outOf;
        }

        deliverable->setGrade(grade, outOf);
        save_gradebook();
        return deliverable_actions(deliverable, category);
    }

    // Delete & Go Back
    else if (choice == 2) {
        save_gradebook();
        category->remove(deliverable);  
    }
    
    deliverable_view(category);
}
