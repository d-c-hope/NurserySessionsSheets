#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <string>
#include <chrono>
#include <vector>
#include <QDate>

namespace TimeUtils {

    std::string timePointDateToString(std::chrono::system_clock::time_point date);
    std::chrono::system_clock::time_point timeStrToTimePointDate(std::string timeStr);
    std::vector<int> getYears();
    std::chrono::system_clock::time_point  dateToTimePoint(int day, int month, int year);
    QDate timePointTQDate(std::chrono::system_clock::time_point date);
    std::chrono::system_clock::time_point  getLaterTimeFromNow(int days);
    std::chrono::system_clock::time_point nextDayAfterTime(std::chrono::system_clock::time_point, int reqDay);
}

#endif // TIMEUTILS_H
