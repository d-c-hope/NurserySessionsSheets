#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <string>
#include <chrono>
#include <vector>

namespace TimeUtils {

    std::string timePointDateToString(std::chrono::system_clock::time_point date);
    std::chrono::system_clock::time_point timeStrToTimePointDate(std::string timeStr);
    std::vector<int> getYears();
    std::chrono::system_clock::time_point  qdateToTimePoint(int day, int month, int year);
}

#endif // TIMEUTILS_H
