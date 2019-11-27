#include "Student.h"
#include <string>
#include <sstream>

using namespace std;

Student::Student()
{

}

Student::Student(int studentID, string name, string level, string major, double GPA, int advisorID)
{
    this->studentID = studentID;
    this->name = name;
    this->level = level;
    this->major = major;
    this->GPA = GPA;
    this->advisorID = advisorID;
}

Student::~Student()
{

}

//converts student info to a string 
string Student::to_string()
{
    //converts ints and doubles to strings using ostringstream
    //found out about this method on c++refrence.com
    ostringstream strs;
    strs << GPA;
    string GPAstr = strs.str(); 
    ostringstream strs2;
    strs2 << studentID;
    string studentIDStr = strs2.str(); 
    string advisorIDStr = "";
    if (advisorID > 0)
    {
        ostringstream strs3;
        strs3 << advisorID;
        advisorIDStr = strs3.str(); 
    }
    else
    {
        //if advisor is listed as -1 that means no advisor and therfore shows as none
        advisorIDStr = "none";
    }

    return string("ID : ") + studentIDStr + ", name: " + name + ", level: " + level + ", major: " 
        + major + ", GPA: " + GPAstr + ", Advisor ID: " + advisorIDStr;
}