#ifndef CHILDLISTEXPORTER_H
#define CHILDLISTEXPORTER_H

#include <vector>
#include <chrono>

#include "child.h"


class ChildListExporter
{
public:
    ChildListExporter(std::vector<Child> children);
    void exportList(std::string filename);


private:
    std::vector<Child> children;
    std::chrono::system_clock::time_point add4Months(std::chrono::system_clock::time_point date);

};

#endif // CHILDLISTEXPORTER_H
