#include "Course.h"
#include <string>
#include <vector>


class Gradebook {
    private:
        std::string student_name;

        std::vector<Course> courses_list;

    public:

        Gradebook();

        Gradebook(std::string filename);

        //Adds a course to the gradebook
        void addCourse();

        // Prints an individual deliverable name and grade
        void printDeliverable(std::string course_name, std::string deliv_name);

        // Prints all grades from the category and category total
        void printCategory(std::string course_name, std::string category_name);

        // Prints the course grade overall
        void printOnlyTotal(std::string course_name);

        // Prints all grades within their respective categories and a course overall
        void printDelivsAndTotal(std::string course_name);

        // Prints only category totals and course overall
        void printCategsAndTotal(std::string course_name);

};