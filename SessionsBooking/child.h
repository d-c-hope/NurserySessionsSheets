#ifndef CHILD_H
#define CHILD_H

#include <string>
#include <chrono>

class Child
{
public:
    int id;
    std::string firstName;
    std::string lastName;
    std::chrono::system_clock::time_point dob;
    Child(int id, std::string firstName, std::string lastName, std::chrono::system_clock::time_point dob);
    Child();
    bool operator== (const Child& other) const;
//    bool operator!= (const Child& other) const;

};

#endif // CHILD_H
