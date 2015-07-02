#ifndef SESSION_H
#define SESSION_H

#include <ctime>
#include <chrono>
#include <iomanip>
#include <vector>


class Sessions
{
public:
    Sessions();
    int childId;
    std::chrono::system_clock::time_point startDate;
    std::vector<std::string> sessionsList;

};

#endif // SESSION_H
