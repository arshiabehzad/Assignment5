#include "Database.h"
#include <string>
#include <cstddef>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    //creates database object
    Database* d = new Database();
    //calls the functions to read in the files
    d->readStudentFile("studentTable.txt");
    d->readFacultyFile("facultyTable.txt");
    //bool used to regulate loop
    bool exit = false;
    while (!exit)
    {
        string line = "";
        cout << "_____________________________________________________________________________________\n" <<
                "Choose from the menu: \n" <<
                "1. Print all students and their information (sorted by ascending id #)\n" <<
                "2. Print all faculty and their information (sorted by ascending id #)\n" <<
                "3. Find and display student information given the students id\n" <<
                "4. Find and display faculty information given the faculty id\n" <<
                "5. Given a student’s id, print the name and info of their faculty advisor\n" <<
                "6. Given a faculty id, print ALL the names and info of his/her advisees.\n" <<
                "7. Add a new student\n" <<
                "8. Delete a student given the id\n" <<
                "9. Add a new faculty member\n" <<
                "10. Delete a faculty member given the id.\n" <<
                "11. Change a student’s advisor given the student id and the new faculty id.\n" <<
                "12. Remove an advisee from a faculty member given the ids\n" <<
                "13. Rollback \n" <<
                "14. Exit \n " << 
                "_____________________________________________________________________________________\n"<<endl;

        cout << "Choice: ";
        cin >> line;
        int choice = stoi(line);
        // switch statement based of users choice
        switch (choice)
        {
            //prints students
            case 1:
                d->printAllStudents();
                cout << endl;
                break;
            //prints faculty
            case 2:
                d->printAllFaculty();
                cout << endl;
                break;
            //finds student
            case 3:
                {
                    string line = "";
                    cout << "Enter student ID of student you want to find: ";
                    cin >> line;
                    int ID = stoi(line);
                    Student* st =  d->findStudent(ID);
                    //insures no segmentation fault
                    if (st != NULL)
                        cout <<st->to_string() <<endl;
                    cout << endl;
                    break;
                }
            // finds faculty 
            case 4:
                {
                    string line = "";
                    cout << "Enter faculty ID of faculty you want to find: ";
                    cin >> line;
                    int ID = stoi(line);
                    Faculty * fa = d->findFaculty(ID);
                    //insures no segmentation fault
                    if (fa != NULL)
                        cout << fa->to_string() <<endl;
                    cout << endl;
                    break;
                }
            //prints students advisor
            case 5:
                {
                    string line = "";
                    cout << "Enter student ID: ";
                    cin >> line;
                    int ID = stoi(line);
                    Faculty *fa = d->findStudentsAdvisor(ID);
                    //insures no segmentation fault
                    if (fa != NULL)
                        cout << "Student's advisor: " << fa->to_string() << endl;
                    cout << endl;
                    break;
                }
            //prints advisees of faculty
            case 6:
                {
                    string line = "";
                    cout << "Enter faculty ID: ";
                    cin >> line;
                    int ID = stoi(line);
                    list<Student*> advisees= d->findFacultyAdvisees(ID);
                    //prints out advisees based of list
                    if (advisees.size() > 0)
                    {
                        cout << "Advisees: " << endl;
                        for (Student* i: advisees )
                        {
                            cout << i->to_string() <<endl;
                        }
                    }
                    cout <<endl;
                    break;
                }
            // add student
            case 7:
                {
                    string line;
                    cout << "Give info about student using ':' as a delimeter: ";
                    //these two lines insure spaces are counted when analyzing input
                    cin.ignore();
                    getline(cin, line);
                    Student* st = d->addStudent(line, false);
                    //adds to action stack so it can be undone in rollback
                    d->actionStack.push(new Action(st, 1));
                    break;
                }
            // deletes a student
            case 8:
                {
                    string line = "";
                    cout << "Give students ID that you want to delete: ";
                    cin >> line;
                    int ID = stoi(line);
                    d->deleteStudent(ID, false);
                    cout <<endl;
                    break;
                }
            //adds a faculty
            case 9:
                {
                    string line;
                    cout << "Give info about faculty using ':' as a delimeter and ',' as a delimeter between advisee IDs (',' after last entry as well): " <<endl;
                    //these two lines insure spaces are counted when analyzing input
                    cin.ignore();
                    getline(cin, line);
                    Faculty* fa = d->addFaculty(line, false);
                    //adds to action stack so it can be undone in rollback
                    d->actionStack.push(new Action(fa, 3));
                    cout << endl;
                    break;
                }
            //deletes a faculty
            case 10:
                {
                    string line = "";
                    cout << "Give faculty ID that you want to delete: ";
                    cin >> line;
                    int ID = stoi(line);
                    d->deleteFaculty(ID, false);
                    cout <<endl;
                    break;
                }
            //change student advisor
            case 11:
                {
                    string line = "";
                    cout << "Give student ID that you want to change advisor for: ";
                    cin >> line;
                    int studentID = stoi(line);
                    line = "";
                    cout << "Give faculty ID that you want to change advisor to: ";
                    cin >> line;
                    int facultyID = stoi(line);
                    d->changeStudentAdvisor(studentID, facultyID, false);
                    cout << endl;
                    break;
                }
            //removes advisee
            case 12:
                {
                    string line = "";
                    cout << "Give faculty ID that you want to remove an advisee from: ";
                    cin >> line;
                    int facultyID = stoi(line);
                    line = "";
                    cout << "Give student ID of the advisee you want to remove: ";
                    cin >> line;
                    int studentID = stoi(line);
                    d->removeAdvisee(studentID, facultyID, false);
                    cout << endl;
                    break;
                }
            //rollback
            case 13:
                d->rollback();
                break;
            //exit
            case 14:
                //breaks loop
                exit = true;
                break;
        }
        //Prints out serialization file
        FILE * sFile = fopen ("seralizedStudentFile.txt","w");
        FILE * fFile = fopen ("seralizedFacultyFile.txt","w");
        d->studentDatabase->serialize(d->studentDatabase->root,sFile);
        d->facultyDatabase->serialize(d->facultyDatabase->root,fFile);
        fclose(sFile); 
        fclose(fFile); 
    }
}