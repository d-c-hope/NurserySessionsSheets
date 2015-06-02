#ifndef CHILD_H
#define CHILD_H

#include <string>
#include <chrono>

class Child
{
public:
    std::string firstName;
    std::string lastName;
    std::chrono::system_clock::time_point dob;
    Child(std::string firstName, std::string lastName, std::chrono::system_clock::time_point dob);
};

#endif // CHILD_H
