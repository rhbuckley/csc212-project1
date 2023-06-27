# csc212-project1
CSC 212 Project

### Summary
### Planning
In our planning process, we came up with two different possible designs. Design A separated the gradebook into 4-5 classes: Student, Course, Category, and Deliverable. It originally had a Grade class as well because we were trying to make it servicable for multiple students to use at once, but we later decided to make it usable for just one student at a time for simplicity's sake, so the Grade class was no longer needed; we could simply store the value in the Deliverable class as a floating point value. Design B was simplified to using only two classes, Gradebook and Course, and stored a list of category and deliverable structs. However, upon observation, we noticed that the algorithm to search through Design B would have a O(n) time complexity, while the organization of pointers in Design A made it possible to have a runtime complexity O(1), so we ended up implementing Design A instead. It is important to note. that though we considered time complexity in our design, we had to backtrack through some of it because it would be a very hard and time consuminng task to figure out how to parse the complex relationships that you will see in the charts below from a text file. 

Below, you can see the two diagrams for Design A (original) and Design A (fixed for input / output)

<img width="922" alt="design-a-original" src="https://github.com/rhbuckley/csc212-project1/assets/42151145/a070e100-38ee-4a37-ae77-d26ce19eb327">

<img width="944" alt="design-a-simple" src="https://github.com/rhbuckley/csc212-project1/assets/42151145/2a1d2962-9283-484f-977f-621d58e9112d">


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

#### Step by Step Commands
1. Open Github Repository under `mvp` branch
2. Press the green code button, and select download as zip
3. Extract the zipped folder to your downloads
4. Open terminal
5. Run `cd ~/Downloads/csc212-project1-mvp`
6. Run `g++ -std=c++11 src/main.cpp src/Interface.cpp src/Gradebook.cpp src/Course.cpp src/Category.cpp src/Deliverable.cpp -o ./gradebookProgram`
7. Run `./gradebookProgram`
8. Done!

This will create an executable file called `gradebookProgram` that will be called at runtime.

Our output is stored by default in a .gradebook file, however, upon first run, if there is no .gradebook file found in the local
directory, the program will ask you if you have a save file somewhere else. 

We have included some sample save files to test with.

There is only one file that is responsible for collecting user input / output, as if this program were to be used in
a real world environment, we would not want I/O helper functions in each of the classes. The interface class is made 
up of a lot of subclasses that really could be separated out into their own files, but keeping all the I/O together is
somewhat important to me (again this is just a command menu). 

There are only two entry conditions for this gradebook:
1. The Gradebook finds an auto-saved file
2. The Gradebook cannot find an auto-saved file
    2a. Do you have one y/n
    2b. If yes, provide path
    
We could have added a CLA as an input for the path, but we decided to make the program more user focused. 

### Our Branches

- mvp (minimum viable product)
    When we started this, we realized we needed a place to save files, so we copy / pasted some of our code and 
    made this branch so we would have a working product to showcase
- development (our ideas branch)
    When we started this project, we did not really consider how we would perform saving user data, and we just came
    up with ideas, created a relationship chart, and started, however, this was a mistake. After going for a while,
  (with semi-functional code), we realized that we needed to save this somewhere, and it would be very very hard to
    save all of the pointer relationships that we had, so we had to scrap some things.

### Runtime instructions

After running the file, you will see a command line interface with options to navigate many different menus to do anything that you may want to do. Keep in mind the 
structure of the program ... Gradebook > Course > Categories > Deliverable. 

### Sample input/output screenshots with brief explanations of the images used

To store our data, we used a rudimentarty custom human readable text format. 

This format has three keywords: BEGIN, END & ADD.

BEGIN and END are used for non-deepest classes, while ADD is used for the deepest data (deliverables).

Here is an example

```
BEGIN GRADEBOOK
   BEGIN COURSE "English"
      BEGIN CATEGORY "Essays"
         ADD DELIVERABLE "Essay 1" 85.0 100.0
         ADD DELIVERABLE "Essay 2" 90.0 100.0
         ADD DELIVERABLE "Essay 3" 80.0 100.0
      END CATEGORY
      BEGIN CATEGORY "Reading"
         ADD DELIVERABLE "Book Report" 95.0 100.0
         ADD DELIVERABLE "Comprehension Quiz" 88.0 100.0
      END CATEGORY
   END COURSE
   BEGIN COURSE "Math"
      BEGIN CATEGORY "Algebra"
         ADD DELIVERABLE "Chapter 1 Test" 92.0 100.0
         ADD DELIVERABLE "Chapter 2 Test" 88.0 100.0
      END CATEGORY
      BEGIN CATEGORY "Geometry"
         ADD DELIVERABLE "Proofs Project" 78.0 100.0
         ADD DELIVERABLE "Triangle Quiz" 90.0 100.0
      END CATEGORY
   END COURSE
END GRADEBOOK
```

Taken from: `sample/.gradebook-1`


<img width="322" alt="Screenshot 2023-06-26 at 9 41 25 PM" src="https://github.com/rhbuckley/csc212-project1/assets/42151145/90dcca1a-f811-4af7-a5d9-1a05be9b88e9">
