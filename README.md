# csc212-project1
CSC 212 Project

### Summary
### Planning
In our planning process, we came up with two different possible designs. Design A separated the gradebook into 4-5 classes: Student, Course, Category, and Deliverable. It originally had a Grade class as well because we were trying to make it servicable for multiple students to use at once, but we later decided to make it usable for just one student at a time for simplicity's sake, so the Grade class was no longer needed; we could simply store the value in the Deliverable class as a floating point value. Design B was simplified to using only two classes, Gradebook and Course, and stored a list of category and deliverable structs. However, upon observation, we noticed that the algorithm to search through Design B would have a O(n) time complexity, while the organization of pointers in Design A made it possible to have a runtime complexity O(1), so we ended up implementing Design A instead.
### Compilation instructions
Before compilation, make sure you have these files downloaded and stored in one folder:
- src/Category.cpp
- src/Category.h
- src/Course.cpp
- src/Course.h
- src/Deliverable.cpp
- src/Deliverable.h
- src/Gradebook.cpp
- src/Gradebook.h
- src/Interface.cpp
- src/Interface.h
- src/main.cpp

Also make sure to include your course input file in the same folder.

Open your terminal and navigate to the folder where your files are located. Once you are there, use the following command to compile the files into an executable:

`g++ -std=c++11 src/main.cpp src/Interface.cpp src/Gradebook.cpp src/Course.cpp src/Category.cpp src/Deliverable.cpp -o ./gradebookProgram`

For convenience’s sake, we included the gradebookProgram compiled file.

This will create an executable file called `gradebookProgram` that will be called at runtime.

Our output is stored by default in a .gradebook file, however, upon first run, if there is no .gradebook file found in the local
directory, the program will ask you if you have a save file somewhere else. 

We have included some sample save files to test with.

There is only one file that is responsible for collecting user input / output, as if this program were to be used in
a real world environment, we would not want I/O helper functions in each of the classes. The interface class is made 
up of a lot of subclasses that really could be separated out into their own files, but keeping all the I/O together is
somewhat important to me (again this is just a command menu). 

### Runtime instructions
### Sample input/output screenshots with brief explanations of the images used
