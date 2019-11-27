#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include "BST.h"
#include "Student.h"
#include "Faculty.h"
#include "Action.h"
using namespace std;

class Database
{
    public:
        //Student and Faculty Trees
        BST <int, Student*>* studentDatabase = new BST<int, Student*>();
        BST <int, Faculty*>* facultyDatabase = new BST<int, Faculty*>();

        //stack used to do rollback
        stack <Action*> actionStack; 

        Database();
        ~Database();

        void readStudentFile(string studentFileName);
        void readFacultyFile(string facultyFileName);
        void printAllStudents();
        void printAllFaculty();
        void addAdvisee(Student* st);
        void deleteStudent(int studentID, bool rollback);
        void deleteFaculty(int facultyID, bool rollback);
        void updateStudentsAdvisor(Faculty* advisor);
        void changeStudentAdvisor(int studentID, int facultyID, bool rollback);
        void removeAdvisee(int studentID, int facultyID, bool rollback);
        void rollback();
        Student* addStudent(string line, bool readFile);
        Student* findStudent(int id);
        Faculty* addFaculty(string line, bool readFile);
        Faculty* findFaculty(int id);
        Faculty* findStudentsAdvisor(int id);
        list<Student*> findFacultyAdvisees(int id);
};