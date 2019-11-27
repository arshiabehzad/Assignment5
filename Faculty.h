#pragma once
#include <string>
#include <list>
using namespace std;

class Faculty 
{
    public:
        //member variables
        int facultyID;
        string name; 
        string level;
        string department;
        list <int> adviseeIDs;

        Faculty();
        Faculty(int facultyID, string name, string level, string department, list <int> adviseeIDs );
        ~Faculty(); 

        string to_string();
};