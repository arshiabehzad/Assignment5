#include "Action.h"
#include <cstddef>

using namespace std;

Action::Action()
{

}

Action::Action(Student* st, Faculty * fa, int action)
{
    this->st = st;
    this->fa = fa;
    this->action = action;
}

Action::Action(Student* st, int action)
{
    this->st = st;
    fa = NULL;
    this->action = action;
}

Action::Action(Faculty * fa, int action)
{
    st = NULL;
    this->fa = fa;
    this->action = action;
}

Action::~Action()
{

}