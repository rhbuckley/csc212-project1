# csc212-project1
CSC 212 Project

### Summary
### Planning
In our planning process, we came up with two different possible designs. Design A separated the gradebook into 4-5 classes: Student, Course, Category, and Deliverable. It originally had a Grade class as well because we were trying to make it servicable for multiple students to use at once, but we later decided to make it usable for just one student at a time for simplicity's sake, so the Grade class was no longer needed; we could simply store the value in the Deliverable class as a floating point value. Design B was simplified to using only two classes, Gradebook and Course, and stored a list of category and deliverable structs. However, upon observation, we noticed that the algorithm to search through Design B would have a O(n) time complexity, while the organization of pointers in Design A made it possible to have a runtime complexity O(1), so we ended up implementing Design A instead.
### Compilation instructions
Before compilation, make sure you have these files downloaded and stored in one folder:
- Category.cpp
- Category.h
- Course.cpp
- Course.h
- Deliverable.cpp
- Deliverable.h
- Gradebook.cpp
- Gradebook.h
- interface.cpp
- interface.h
- main.cpp

Also make sure to include your course input file in the same folder.

Open your terminal and navigate to the folder where your files are located. Once you are there, use the following command to compile the files into an executable:

`g++ -std=c++11 main.cpp interface.cpp Gradebook.cpp Course.cpp Category.cpp Deliverable.cpp -o gradebook`

This will create an executable file called `gradebook` that will be called at runtime.

### Runtime instructions
### Sample input/output screenshots with brief explanations of the images used
