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

int Interface::drawMenuFromInput(const std::string &msg, std::vector<std::string> menu) {
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
            return drawMenuFromInput(msg, menu);
        }

        // Return choice
        return choice;
    } catch (const std::exception &e) {
        std::cout << "Invalid Selection" << std::endl;
        return drawMenuFromInput(msg, menu);
    }

}

void Interface::displayWelcome() {
    std::vector<std::string> menu = {
            "View Classes",
            "Add a Class",
            "Delete a Class",
            "Exit"
    };

    int choice = 0;  // placeholder
    while (choice <= 0 || choice > menu.size())
        choice = drawMenuFromInput("Welcome", menu);

    if (choice == 1) return showClassView();
    if (choice == 2) return classCreationWiz();
    if (choice == 3) return classDeletionWiz();
}

void Interface::showClassView() {
    std::vector<Course*> courses = gb.getCourses();
    std::vector<std::string> courseNames;

    if (courses.size() == 0) {
        std::cout << "You aren't registered in any courses" << std::endl;
        return displayWelcome();
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

    int choice = drawMenuFromInput("Select a Course to Proceed", courseNames);
    if (choice != courseNames.size()) return displayCourseMenu(courses[choice - 1]);

    // go back to main menu
    return displayWelcome();
}

void Interface::classCreationWiz() {
    std::string className;

    std::cout << "Enter Class Name for this course" << std::endl;

    // the name isn't a key so though I don't know why a user may want
    // to name their classes the same, they can
    std::cout << "? ";
    std::cin.ignore();
    std::getline(std::cin, className);

    gb.appendCourse(Course(className));
    // we made a change, save it
    saveFile();

    // go back to main menu
    return displayWelcome();
}

void Interface::classDeletionWiz() {
    std::vector<Course*> courses = gb.getCourses();
    std::vector<std::string> courseNames;

    if (courses.empty()) {
        std::cout << "You aren't registered in any courses" << std::endl;
        return displayWelcome();
    }

    for (Course *course : courses)
        courseNames.push_back(course->getName());

    courseNames.emplace_back("Cancel");

    int choice = drawMenuFromInput("Select a Course to Delete", courseNames);

    if (choice != courseNames.size()) {
        gb.removeCourse(courses[choice - 1]);
        saveFile();
        std::cout << "Saved" << std::endl;
    }
    return displayWelcome();
}

void Interface::displayCourseMenu(Course *course) {
    std::vector<std::string> choices = {
            "View Assignment Categories",
            "Add Assignment Category",
            "Delete Assignment Category",
            "Home"
    };

    int choice = drawMenuFromInput("Select an Option to Proceed", choices);

    if (choice == 1) return displayCourseCategories(course);
    if (choice == 2) return categoryCreationWiz(course);
    if (choice == 3) return categoryDeletionWiz(course);

    if (choice == 4) return displayWelcome();
}

void Interface::displayCourseCategories(Course *course){
    std::vector<std::string> choices;

    for (Category *category : course->getAllCategories())
        choices.push_back(category->getName());

    if (choices.empty()) {
        std::cout << "There are no available categories!" << std::endl;
        return displayCourseMenu(course);
    }

    choices.emplace_back("Go Back");

    int choice = drawMenuFromInput("Select a Category to Proceed", choices);

    if (choice == choices.size()) return displayCourseMenu(course);
    return displayCourseCategoryDeliverables(course->getAllCategories()[choice - 1]);
}

void Interface::categoryCreationWiz(Course* course) {
    std::string cat_name;
    std::cout << "Enter name for new category" << std::endl;
    std::cout << "? ";
    std::cin.ignore();
    std::getline(std::cin, cat_name);

    course->addCategory(Category(cat_name));
    saveFile();
    return displayCourseCategories(course);    
}

void Interface::categoryDeletionWiz(Course* course) {
    std::vector<std::string> choices;

    for (Category *category : course->getAllCategories())
        choices.push_back(category->getName());

    choices.emplace_back("Go Back");

    int choice = drawMenuFromInput("Delete a Category", choices);
    if (choice == choices.size() + 1) return displayCourseCategories(course);

    course->removeCategory(course->getAllCategories()[choice - 1]);
    saveFile();
    return displayCourseCategories(course);
}

void Interface::displayCourseCategoryDeliverables(Category* category){
    std::vector<std::string> choices;

    for (Deliverable *deliverable : category->getDeliverables())
        choices.push_back(deliverable->getName() + " " + std::to_string((int)deliverable->getPercentage()) + "%");

    choices.emplace_back("Add New Deliverable");
    choices.emplace_back("Go Home");

    int choice = drawMenuFromInput("Select a Deliverable to Edit or Delete", choices);

    if (choice == choices.size() - 1) return deliverableCreationWiz(category);
    if (choice == choices.size()) return displayWelcome();
    return displayDeliverableDetails(category->getDeliverables()[choice - 1], category);
}

void Interface::deliverableCreationWiz(Category *category) {
    std::cout << "Enter a name for the deliverable" << std::endl;
    std::cout << "? ";
    std::string input;
    std::cin.ignore();
    std::getline(std::cin, input);

    double score, maxScore;
    std::cout << "Enter Your Score and Maximum Possible Score. (e.g. 80 100 would be equivalent to 80%)" << std::endl;
    std::cin >> score >> maxScore;

    category->append(Deliverable(input, score, maxScore));
    saveFile();
    return displayCourseCategoryDeliverables(category);
}

void Interface::displayDeliverableDetails(Deliverable* deliverable, Category* category) {
    std::vector<std::string> choices = {
        "Edit",
        "Delete",
        "Back",
    };

    std::cout << "Deliverable: " << deliverable->getName() << std::endl;
    std::cout << "Scored: " << deliverable->getGrade() << " / " << deliverable->getMaxPts() << std::endl;

    int choice = drawMenuFromInput("Select Action", choices);

    // Edit
    if (choice == 1) {
        int grade = -1, outOf = -1;

        // todo: add input validation so a char doesn't crash
        while (grade < 0 && outOf < 0) {
            std::cout << "Please Enter your New Grade SPACE Out Of Many Points. e.g. (80 100) which would be 80%" << std::endl;
            std::cin >> grade >> outOf;
        }

        deliverable->setGrade(grade, outOf);
        saveFile();
        return displayDeliverableDetails(deliverable, category);
    }

    // Delete & Go Back
    else if (choice == 2) {
        saveFile();
        category->remove(deliverable);  
    }
    
    displayCourseCategoryDeliverables(category);
}
