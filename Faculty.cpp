#include "Faculty.h"
#include <string>
#include <sstream>

using namespace std;

Faculty::Faculty()
{

}

Faculty::Faculty(int facultyID, string name, string level, string department, list<int> adviseeIDs)
{
    this->facultyID = facultyID;
    this->name = name;
    this->level = level;
    this->department = department;
    this->adviseeIDs = adviseeIDs;
}

Faculty::~Faculty()
{

}

//converts faculty info to a string 
string Faculty::to_string()
{

    //converts ints to strings using ostringstream
    //found out about this method on c++refrence.com
    ostringstream strs2;
    strs2 << facultyID;
    string facultyIDStr = strs2.str();
    string adviseesStr = "";
    //converts list of advisees to a string
    if (adviseeIDs.size() > 0)
    {
        ostringstream strs3;
        for (int i: adviseeIDs)
        {
            strs3 << i << ", ";
        }
        adviseesStr = strs3.str();
    }
    else
    {
        //if advisee list is empty lists as empty
        adviseesStr = "none";
    }
    
    return string("ID : ") + facultyIDStr + ", name: " + name + ", level: " + level + 
        ", department: " + department + ", Advisee IDs: " + adviseesStr;
}