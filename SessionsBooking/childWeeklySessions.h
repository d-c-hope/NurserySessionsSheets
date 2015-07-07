#ifndef CHILD_WEEKLY_SESSIONS_H
#define CHILD_WEEKLY_SESSIONS_H

#include <ctime>
#include <chrono>
#include <iomanip>
#include <vector>


class ChildWeeklySessions
{
public:
    ChildWeeklySessions();
    int childId = -1;
    std::chrono::system_clock::time_point startDate;
    std::chrono::system_clock::time_point endDate;
    bool isTemporary;
    std::vector<std::string> sessionsList;

};

#endif // CHILD_WEEKLY_SESSIONS_H
