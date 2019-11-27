#include "Database.h"
#include <string>
#include <list>
#include <stdio.h>
#include <stdlib.h>    
#include <time.h> 

//instantiates BSTs
Database::Database()
{
    BST<int, Student *> *studentDatabase = new BST<int, Student *>();
    BST<int, Faculty *> *facultyDatabase = new BST<int, Faculty *>();
}

Database::~Database()
{
    
}

/*Reads student file by opening the file,
then it calls add student in which its actually is added to the database*/
void Database::readStudentFile(string studentFileName)
{   
    string line = "";
    ifstream studentFile;
    studentFile.open(studentFileName);
    //makes sure that the file can be opened
    if (studentFile.is_open())
    {
        //keeps going until they reach the end of the file
        while (studentFile.eof() == false)
        {
            //gets the line in the file
            getline(studentFile, line);
            addStudent(line, true);
        }
    }
    //closes the file
    studentFile.close();
}

/*This function is used in two different scenarios in this current implementation:
1)adding a student to the database from a file
2)adding a student to the database when directed to by the user while using the program

The function knows which scenario it is in by what the value of the bool readFile is  

Students info being added must be seperated by the delimeter ':'
This is the format:
ID:Name:Level:Major:GPA:AdvisorID
*/
Student* Database::addStudent(string line, bool readFile)
{
    //gets everything before the first ':' and adds it to the studentID variable
    int studentID = stoi(line.substr(0, line.find(':')));
    //makes the string line be the rest of the string (not including studentID)
    line = line.substr(line.find(':')+1);

    string name = line.substr(0, line.find(':'));
    line = line.substr(line.find(':')+1);

    string level = line.substr(0, line.find(':'));
    line = line.substr(line.find(':')+1);

    string major = line.substr(0, line.find(':'));
    line = line.substr(line.find(':')+1);

    double GPA = stod(line.substr(0, line.find(':')));
    line = line.substr(line.find(':')+1);

    int advisorID;
    //checks wether or not student advisor is given
    if (line.length() > 0)
    {
        advisorID = stoi(line);
    }
    else
    {
        // an advisor ID of -1 means student does not have advisor 
        advisorID = -1;
    }
    //creates new Student object with the variables that were just set
    Student* st = new Student(studentID, name, level, major, GPA, advisorID);
    //adds student to database and stores wether or not the key was valid
    bool validKey = studentDatabase->insert(studentID, st);
    //if the key is valid and it is not during the readFile process it will update advisees 
    if (validKey && !readFile)
        addAdvisee(st);
    //if the key was valid it will print to the user that it was sucesfull
    if (validKey)
        cout << "Student sucessfully added" <<endl;
    //returns the student that was added to the database
    return st;
}

/*Reads faculty file by opening the file,
then it calls add faculty in which its actually is added to the database
very similar to readStudentFile()function */
void Database::readFacultyFile(string facultyFileName)
{
    string line = "";
    ifstream facultyFile;
    facultyFile.open(facultyFileName);
    if (facultyFile.is_open())
    {
        while (facultyFile.eof() == false)
        {
            getline(facultyFile, line);

            addFaculty(line, true);
        }
    }
    facultyFile.close();
}

/*This function is used in two different scenarios in this current implementation:
1)adding a faculty to the database from a file
2)adding a student to the database when directed to by the user while using the program

The function knows which scenario it is in by what the value of the bool readFile is  

Faculty memebers info being added must be seperated by the delimeter ':'
This is the format:
ID:Name:Level:Department:adviseeID1, adviseeID2, adviseeID3,

*****NOTE: MUST ADD COMMA AFTER LAST ADVISEE ID FOR FUNCTION TO WORK********
*/
Faculty * Database::addFaculty(string line, bool readFile)
{
    int facultyID = stoi(line.substr(0, line.find(':')));
    line = line.substr(line.find(':') + 1);
    //cout << "Faculty ID: " << facultyID << endl;

    string name = line.substr(0, line.find(':'));
    line = line.substr(line.find(':') + 1);
    //cout << "name: " << name << endl;

    string level = line.substr(0, line.find(':'));
    line = line.substr(line.find(':') + 1);
    //cout << "level: " << level << endl;

    string department = line.substr(0, line.find(':'));
    line = line.substr(line.find(':') + 1);
    //cout << "major: " << department << endl;

    //creates a list of integers to store all advisor IDs
    list <int> adviseeIDs;
    while (line.length() > 1)
    {
        //adds adviseeIDs to list seperated by commas
        adviseeIDs.push_back(stoi(line.substr(0, line.find(','))));
        line = line.substr(line.find(',') + 1);
    }

    //implementation is the same as addStudent() except obviously done for faculty
    Faculty *fa = new Faculty(facultyID, name, level, department, adviseeIDs);
    bool validKey = facultyDatabase->insert(facultyID, fa);
    if (validKey && !readFile)
        updateStudentsAdvisor(fa);
    if (validKey)
        cout << "Faculty member sucessfully added" <<endl;
    return fa;
}

/*This function updates the students advisors based on the new faculty memeber that
was added's advisees list */
void Database::updateStudentsAdvisor(Faculty* advisor)
{
    list<int> adviseeIDs = advisor->adviseeIDs;
    for (int i: adviseeIDs)
    {
        Student *st = studentDatabase->searchKey(i);
        //error checking (see README)
        if (st == NULL)
        {
            cout << "WARNING: Student with supposed ID: " << i << " is listed as advisee but does not exist" << endl;
            //continues to next advisee in the list
            continue;
        }
        // if student doesnt have advisor, updates student to have advisor
        if (st->advisorID < 0)
        {
            st->advisorID = i;
        }
        //error checking (see README)
        else if (st->advisorID != i)
        {
            cout << "WARNING: Student with ID: " << i << 
            " already has an advisor, student's advisor was not changed.\n" 
            << "If you want to change student's advisor use menu option 11" << endl;;
        }
    }
}

/*Deletes student given student ID
@param bool rollback determines wether or not function is being called normally
or as part as the rollback function

This insures that if it is a rollback that the action is not added to the action
stack  */
void Database::deleteStudent(int studentID, bool rollback)
{
    // deletes student and saves student that got deleted to variable
    Student * st = studentDatabase->deleteNode(studentID);
    //error checking (see README)
    if (st == NULL)
    {
        cout << "Student you are trying to delete does not exist" << endl;
        return;
    }
    // updates advisees list of deleted students advisor
    int advisorID = st->advisorID;
    Faculty * advisor = facultyDatabase->searchKey(advisorID);
    //error checking (see README)
    if (advisor == NULL)
    {
        cout << "Student sucessfully deleted" <<endl;
        //if this method is not called through the rollback function
        if (!rollback)
            //adds action to the action stack 
            actionStack.push(new Action(st, 2));
        return;
    }
    advisor->adviseeIDs.remove(studentID);
    cout << "Student sucessfully deleted" <<endl;
    //if this method is not called through the rollback function
    if (!rollback)
        //adds action to the action stack 
        actionStack.push(new Action(st, 2));
}


/*Deletes faculty given faculty ID
@param bool rollback determines wether or not function is being called normally
or as part as the rollback function

This insures that if it is a rollback that the action is not added to the action
stack  */
void Database::deleteFaculty(int facultyID, bool rollback)
{
    Faculty * fa = facultyDatabase->deleteNode(facultyID);
    //error checking (see README)
    if (fa == NULL)
    {
        cout << "Faculty member you are trying to delete does not exist" << endl;
        return;
    }
    // updates students' advisors
    int advisorID = fa->facultyID;
    //saves the list of adviseeIDs
    list<int> adviseeIDs = fa->adviseeIDs;
    for (int i: adviseeIDs)
    {
        Student * st = studentDatabase->searchKey(i);
        //if student doesn't exist continues to next on in the list
        if (st == NULL)
            continue;
        // sets student advisor ID to -1 (meaning it doesnt have and advisor)
        st->advisorID = -1;
    }
    cout << "Faculty member sucessfully deleted" <<endl;
    //if this method is not called through the rollback function
    if (!rollback)
        //adds action to the action stack 
        actionStack.push(new Action(fa, 4));
}

/*Changes a student's advisor given the studentID and facultyID

@param bool rollback determines wether or not function is being called normally
or as part as the rollback function
*/
void Database::changeStudentAdvisor(int studentID, int facultyID, bool rollback)
{
    //saves student whose advisor is being changed
    Student* st = studentDatabase->searchKey(studentID);
    //error checking (see README)
    if (st == NULL)
    {
        cout << "Student does not exist" << endl;
        return;
    }
    //stores student's old advisor ID in a variable
    int oldAdvisorID = st->advisorID;
    //changes the students advisor
    st->advisorID = facultyID;
    Faculty * oldAdvisor;
    if (oldAdvisorID > 0)
    {
        //stores old advisor object
        oldAdvisor = facultyDatabase->searchKey(oldAdvisorID);
        //removes student from old advisor's list of advisees
        oldAdvisor->adviseeIDs.remove(studentID);
    }
    //adds student to new advisors list of advisees
    Faculty * fa = facultyDatabase->searchKey(facultyID);
    //error checking (see README)
    if (fa == NULL)
    {
        cout << "Faculty does not exist" << endl;
        return;
    }
    fa->adviseeIDs.push_back(studentID);

    cout << "Student's advisor sucessfully changed" <<endl;
    if (!rollback)
        //adds action to action stack
        actionStack.push(new Action(st, oldAdvisor, 5));
}

/*Removes a faculty's advisee given the studentID and facultyID

@param bool rollback determines wether or not function is being called normally
or as part as the rollback function
*/
void Database::removeAdvisee(int studentID, int facultyID, bool rollback)
{
    Faculty * fa = facultyDatabase->searchKey(facultyID);
    Student * st = studentDatabase->searchKey(studentID);
    //error checking (see README)
    if (fa == NULL)
    {
        cout << "Faculty does not exist" << endl;
        return;
    }
    //error checking (see README)
    if (st == NULL)
    {
        cout << "Student does not exist" << endl;
        return;
    }
    if (!rollback)
        actionStack.push(new Action(st, fa, 6));

    //removes advisee from advisee list
    fa->adviseeIDs.remove(studentID);
    //removes advisor from student
    st->advisorID = -1;

    cout << "Advisee sucessfully removed" <<endl;
}

/*Called during addStudent() function 
makes sure that referential integrity is mantained by updating the advisee list*/
void Database::addAdvisee(Student* st)
{
    // if student doesnt have an advisor listed stops the function
    if(st->advisorID == -1)
    {
        return;
    }
    Faculty* advisor = facultyDatabase->searchKey(st->advisorID);
    //error checking (see README)
    if (advisor == NULL)
    {
        cout << "WARNING: Student's advisor does not exist" << endl;
        return;
    }
    int studentID = st->studentID;
    list<int> adviseeIDs = advisor->adviseeIDs;
    for (int i: adviseeIDs)
    {
        //if student already listed as advisee stops function
        if (i == studentID)
        {
            return;
        }
    }
    //if student not listed as advisee adds student to advisee list
    advisor->adviseeIDs.push_back(studentID);
}

/*
Allows user to undo action (theoretically unlimited times)
Uses the action stack to determine what action was done, and how to undo it
This is determined on the Action member variable int action
This is the key:
action = 1 means that a student was added, therefore to undo we must delete
action = 2 means that student was deleted, therfore to undo we must add
action = 3 means that a faculty was added, therfore to undo we must delete
action = 4 means that a faculty was deleted, therfore undo we must add
action = 5 means that an advisor was changed, therfore we must change it back
action = 6, means that an advisee was removed, therfore it must be added back

Using the Faculty* and Student* member variables from the Action object the rollback
function can sucesfully undo these actions as it has stored the objects that are necesarry
to call the opposing function
*/
void Database::rollback()
{
    // if there is nothing in the stack, rollback is not possible so it stops the function
    if (actionStack.size() < 1)
    {
        cout << "No actions to rollback" <<endl;
        return;
    }
    //stores the action on top of the stack
    Action* actionToUndo = actionStack.top();
    //pops of the action off the list
    actionStack.pop();
    //stores the action number to see which action was done
    int numAction = actionToUndo->action;
    //determines which action was done so it knows how to undo it
    switch (numAction)
    {
        //student was added, therefore to undo we must delete
        case 1:
            deleteStudent(actionToUndo->st->studentID, true);
            cout << "\nadding of student was undone" <<endl;
            break;
        //student was deleted, therfore to undo we must add
        case 2:
            studentDatabase->insert(actionToUndo->st->studentID, actionToUndo->st);
            addAdvisee(actionToUndo->st);
            cout << "\ndeletion of student was undone" <<endl;
            break;
        //faculty was added, therfore to undo we must delete
        case 3:
            deleteFaculty(actionToUndo->fa->facultyID, true);
            cout << "\nadding of faculty was undone" <<endl;
            break;
        //faculty was deleted, therfore undo we must add
        case 4:
            facultyDatabase->insert(actionToUndo->fa->facultyID, actionToUndo->fa);
            updateStudentsAdvisor(actionToUndo->fa);
            cout << "\ndeletion of faculty was undone" <<endl;
            break;
        //advisor was changed, therfore we must change it back
        case 5:
            changeStudentAdvisor(actionToUndo->st->studentID, actionToUndo->fa->facultyID, true);
            cout << "\nchanging of student advisor was undone" << endl;
            break;
        //advisee was removed, therfore it must be added back
        case 6:
            changeStudentAdvisor(actionToUndo->st->studentID, actionToUndo->fa->facultyID, true);
            cout << "\ndeleting of advisee was undone" << endl;
            break;
    }
}

//print all students
void Database::printAllStudents()
{
    studentDatabase->printTree();
}

//print all falculty
void Database::printAllFaculty()
{
    facultyDatabase->printTree();
}

//returns student in database given student ID
Student* Database::findStudent(int id)
{
    Student *st = studentDatabase->searchKey(id);
    //error checking (see README)
    if (st == NULL)
    {
        cout << "Student not found" << endl;
        return NULL;
    }
    return st;
}

//returns faculty in database given faculty ID
Faculty* Database::findFaculty(int id)
{
    Faculty *fa = facultyDatabase->searchKey(id);
    //error checking (see README)
    if (fa == NULL)
    {
        cout << "Faculty member not found" << endl;
        return NULL;
    }
    return fa;
}

//finds a students advisor given student ID
Faculty* Database::findStudentsAdvisor(int id)
{
    Student *st = studentDatabase->searchKey(id);
    //error checking (see README)
    if (st == NULL)
    {
        cout << "Student does not exist" << endl;
        return NULL;
    }
    int advisorID = st->advisorID;
    //error checking (see README)
    //this means student was not paired with an advisor
    if (advisorID == -1)
    {
        cout << "Student not paired with advisor" << endl;
        return NULL;
    }
    Faculty *fa = facultyDatabase->searchKey(advisorID);
    //error checking (see README)
    if (fa == NULL)
    {
        cout << "Students listed advisor does not exist." << endl;
        return NULL;
    }
    return fa;
}

//returns list of advisees(Students) for a faculty given faculty ID
list<Student*> Database::findFacultyAdvisees(int id)
{
    list<Student*> adviseeList; 
    Faculty *fa = facultyDatabase->searchKey(id);
    //error checking (see README)
    if (fa == NULL)
    {
        cout << "Faculty member does not exist" << endl;
        //returns empty list
        return adviseeList;
    }
    list<int> adviseeListIDs = fa->adviseeIDs;
    //adds Students to list of Students based of adviseeIDs
    for (int i: adviseeListIDs)
    {
        Student *st = studentDatabase->searchKey(i);
        //of student exsists adds to list of students
        if (st != NULL)
            adviseeList.push_back(st);
        else 
            cout << "WARNING: Although listed as advisee, student with ID: " << i << " was not found" << endl;
    }
    return adviseeList;
}
