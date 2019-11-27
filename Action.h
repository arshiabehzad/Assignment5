#pragma once
#include <string>
#include "Student.h"
#include "Faculty.h"
using namespace std;

/*This class is used to keep track of actions done by the user, and the objects these actions were 
done to so that their actions can be undone if the rollback function is called
The action member variable is an integer that is used in the rollback function to determine
what action was done by the user, and what to do to reverse it 
This is the key:
action = 1 means that a student was added
action = 2 means that student was deleted
action = 3 means that a faculty was added
action = 4 means that a faculty was deleted
action = 5 means that an advisor was changed
action = 6, means that an advisee was removed
*/
class Action
{
    public:
        Student* st;
        Faculty * fa;
        int action;

        Action();
        Action(Student* st, Faculty * fa, int action);
        Action(Student* st, int action);
        Action(Faculty* fa, int action);
        ~Action();
        

};