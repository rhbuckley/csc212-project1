//
// Created by Richard Buckley on 6/25/23.
//

#include "Interface.h"

Interface::Interface() {
    // welcome message
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

    // display subject message
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
    // define menu for entrypoint
    std::vector<std::string> menu = {
            "View Classes",
            "Add a Class",
            "Delete a Class",
            "Exit"
    };

    // get choice
    int choice = generate_menu_get_choice("Welcome", menu);

    // delve deeper into program
    if (choice == 1) return course_view();
    if (choice == 2) return course_create();
    if (choice == 3) return course_delete();
}

void Interface::course_view() {
    // get courses
    std::vector<Course*> courses = gb.getCourses();

    // empty course names
    std::vector<std::string> courseNames;

    // check if empty
    if (courses.empty()) {
        // disallow from using this function
        std::cout << "You aren't registered in any courses" << std::endl;
        return interface_entrypoint();
    }

    // generate string for course
    for (Course *course : courses) {
        // temp string
        std::string temp;

        // add name
        temp = course->getName();
        temp += " - ";

        // check if we can give a percentage
        if (!course->getAllDeliverables().empty())
            temp += std::to_string((int)course->getPercentage()) + "%";
        else
            temp += "NA";

        // add to vector
        courseNames.push_back(temp);
    }

    // add exit command as well
    courseNames.emplace_back("Exit");

    // display menu, and check for exit
    int choice = generate_menu_get_choice("Select a Course to Proceed", courseNames);

    // this might be a bit confusing in hindsight here, Exit was appended to courseNames, so exit will
    // add one to the courseNames size
    if (choice != courseNames.size()) return course_actions(courses[choice - 1]);

    // go back to main menu
    return interface_entrypoint();
}

void Interface::course_create() {
    // temp class name
    std::string className;

    std::cout << "Enter Class Name for this course" << std::endl;

    // the name isn't a key so though I don't know why a user may want
    // to name their classes the same, they can
    std::cout << "? ";

    // this cin.ignore prevents the getline from seeing an earlier \n and skipping
    std::cin.ignore();

    // and now we can get line (had some issues without the cin.ignore)
    std::getline(std::cin, className);

    // add the course
    gb.appendCourse(Course(className));

    // we made a change, save it
    save_gradebook();

    // go back to main menu
    return interface_entrypoint();
}

void Interface::course_delete() {
    // get all courses
    std::vector<Course*> courses = gb.getCourses();

    // empty vector for course names
    std::vector<std::string> courseNames;

    // check to make sure that we can allow the user to come here
    if (courses.empty()) {
        std::cout << "You aren't registered in any courses" << std::endl;
        return interface_entrypoint();
    }

    // get the course names
    for (Course *course : courses)
        courseNames.push_back(course->getName());

    // add a cancel button (just in case)
    courseNames.emplace_back("Cancel");

    // get user choice
    int choice = generate_menu_get_choice("Select a Course to Delete", courseNames);

    // again, we added "Cancel" to courseNames, so this may look confusing (it works)
    if (choice != courseNames.size()) {

        // remove & save
        gb.removeCourse(courses[choice - 1]);
        save_gradebook();
    }

    // go home
    return interface_entrypoint();
}

void Interface::course_actions(Course *course) {
    // this is an entrypoint to what choices can be made on a course
    std::vector<std::string> choices = {
            "View Assignment Categories",
            "Add Assignment Category",
            "Delete Assignment Category",
            "Home"
    };

    // get user choice
    int choice = generate_menu_get_choice("Select an Option to Proceed", choices);

    // map choice to function
    if (choice == 1) return categories_view(course);
    if (choice == 2) return categories_create(course);
    if (choice == 3) return categories_delete(course);
    if (choice == 4) return interface_entrypoint();
}

void Interface::categories_view(Course *course){
    // get categories
    std::vector<std::string> choices;

    // can we allow user to come here?
    if (course->getAllCategories().empty()) {
        std::cout << "There are no available categories!" << std::endl;
        return course_actions(course);
    }

    // categories -> category names
    for (Category *category : course->getAllCategories())
        choices.push_back(category->getName());

    // add back button to choices
    choices.emplace_back("Go Back");

    // get user choice
    int choice = generate_menu_get_choice("Select a Category to Proceed", choices);

    // allow going backwards
    if (choice == choices.size()) return course_actions(course);

    // view the deliverables in the category
    return deliverable_view(course->getAllCategories()[choice - 1]);
}

void Interface::categories_create(Course* course) {

    // create a category
    std::string cat_name;
    std::cout << "Enter name for new category" << std::endl;
    std::cout << "? ";

    // again, ignore for getline
    std::cin.ignore();
    std::getline(std::cin, cat_name);

    // add the category & save gradebook
    course->addCategory(Category(cat_name));
    save_gradebook();

    // go back to category view
    return categories_view(course);
}

void Interface::categories_delete(Course* course) {
    std::vector<std::string> choices;

    // find all categories that we can delete. we shouldn't
    // need to guard this function as its parent is guarded
    for (Category *category : course->getAllCategories())
        choices.push_back(category->getName());

    // add a back button
    choices.emplace_back("Go Back");

    // get user choice
    int choice = generate_menu_get_choice("Delete a Category", choices);

    // enable back button (add one because we are converting 0 index to 1 index)
    if (choice == choices.size() + 1) return categories_view(course);

    // remove the category
    course->removeCategory(course->getAllCategories()[choice - 1]);

    // save gradebook
    save_gradebook();

    // return to categories view
    return categories_view(course);
}

void Interface::deliverable_view(Category* category){
    std::vector<std::string> choices;

    // format deliverables for viewing
    for (Deliverable *deliverable : category->getDeliverables())
        choices.push_back(deliverable->getName() + " " + std::to_string((int)deliverable->getPercentage()) + "%");

    // add custom options
    choices.emplace_back("Add New Deliverable");
    choices.emplace_back("Go Home");

    // get user choice
    int choice = generate_menu_get_choice("Select a Deliverable to Edit or Delete", choices);

    // map choice to actions / sub-functions

    // subtracting 1 because this should be the second to last element
    if (choice == choices.size() - 1) return deliverable_create(category);
    if (choice == choices.size()) return interface_entrypoint();

    // perform action
    return deliverable_actions(category->getDeliverables()[choice - 1], category);
}

void Interface::deliverable_create(Category *category) {
    // Get name of deliverable
    std::cout << "Enter a name for the deliverable" << std::endl;
    std::cout << "? ";

    // get input & ignore so it works
    std::string input;
    std::cin.ignore();
    std::getline(std::cin, input);

    // get information needed for deliverable
    double score, maxScore;
    std::cout << "Enter Your Score and Maximum Possible Score. (e.g. 80 100 would be equivalent to 80%)" << std::endl;
    std::cin >> score >> maxScore;

    // add deliverable
    category->append(Deliverable(input, score, maxScore));

    // save & go back
    save_gradebook();
    return deliverable_view(category);
}

void Interface::deliverable_actions(Deliverable* deliverable, Category* category) {
    // give default choices
    std::vector<std::string> choices = {
        "Edit",
        "Delete",
        "Back",
    };

    // deliverable display
    std::cout << "Deliverable: " << deliverable->getName() << std::endl;
    std::cout << "Scored: " << deliverable->getGrade() << " / " << deliverable->getMaxPts() << std::endl;

    // get user choice
    int choice = generate_menu_get_choice("Select Action", choices);

    // Edit
    if (choice == 1) {
        // default values, so we can do some validation
        int grade = -1, outOf = -1;

        // todo: add input validation so a char doesn't crash
        while (grade < 0 && outOf < 0) {
            std::cout << "Please Enter your New Grade SPACE Out Of Many Points. e.g. (80 100) which would be 80%" << std::endl;
            std::cin >> grade >> outOf;
        }

        // set the grade
        deliverable->setGrade(grade, outOf);

        // save & go back
        save_gradebook();
        return deliverable_actions(deliverable, category);
    }

    // Delete & Go Back
    else if (choice == 2) {
        save_gradebook();
        category->remove(deliverable);  
    }

    // guess we must need to go back
    return deliverable_view(category);
}
