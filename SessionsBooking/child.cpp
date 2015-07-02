#include "child.h"


Child::Child()
{
    this->firstName = "";
    this->lastName = "";
}


Child::Child(int id, std::string firstName, std::string lastName, std::chrono::system_clock::time_point dob)
{
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
    this->dob = dob;
}


bool Child::operator== (const Child& child) const {
    if ( (firstName == child.firstName) && (lastName == child.lastName) &&
         (dob == child.dob) && (id == child.id)) {
        return true;
    }
    else return false;
}
