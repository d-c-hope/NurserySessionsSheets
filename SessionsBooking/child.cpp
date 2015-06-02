#include "child.h"

Child::Child(std::string firstName, std::string lastName, std::chrono::system_clock::time_point dob)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->dob = dob;
}
