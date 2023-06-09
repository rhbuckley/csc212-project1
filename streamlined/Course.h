#include <string>
#include <vector>


//Structure to hold the necessary info for each course deliverable
struct Deliverable{
    std::string name;
    std::string category;
    double grade;
    double out_of;
};


class Course {
    protected:
        // Name of the course
        std::string course_name;
        // Method of calculating grade (point-scale, weighted average, etc)
        // Affects how we calculate the grade; it might be better to just 
        // focus on one calculation method and ignore this
        std::string grading_type;

        // List of course deliverables
        std::vector<Deliverable> deliv_list;
        // List of category names
        std::vector<std::string> category_list;

    public:

        Course();

        Course(std::string name);

        Course(std::string name, std::string grading_type);

        // Add new deliverable to the course 
        void addDeliverable(Deliverable new_deliv);

        // Returns the name of the course
        std::string getCourseName();

        // Calculates and returns an individual deliverable grade
        double getIndividualGrade(std::string deliv_name);

        // Calculates and returns the total grade of a category
        double getCategoryGrade(std::string category_name);

        // Calculates and returns the course grade overall
        double getTotalGrade();

};