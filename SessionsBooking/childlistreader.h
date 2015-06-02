#ifndef CHILDLISTREADER_H
#define CHILDLISTREADER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "child.h"


class ChildListReader
{
public:
    ChildListReader();
    std::vector<Child> readList(std::string filename);
};

#endif // CHILDLISTREADER_H
