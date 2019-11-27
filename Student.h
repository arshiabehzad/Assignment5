#pragma once
#include <string>
using namespace std;

class Student
{
    public:
        //member variables
        int studentID;
        string name; 
        string level;
        string major;
        double GPA;
        int advisorID;

        Student();
        Student(int studentID, string name, string level, string major, double GPA, int advisorID);
        ~Student(); 

        string to_string();




};