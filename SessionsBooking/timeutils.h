#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <string>
#include <chrono>
#include <vector>
#include <tuple>
#include <QDate>

namespace TimeUtils {

    const std::vector<std::string> months = {"January", "February", "March", "April", "May", "June", "July","August","September","October","November","December"};

    std::string timePointDateToString(std::chrono::system_clock::time_point date);
    std::chrono::system_clock::time_point timeStrToTimePointDate(std::string timeStr);
    std::vector<int> getYears(int prev, int next);
    std::chrono::system_clock::time_point  dateToTimePoint(int day, int month, int year);
    std::tuple<int, int, int> timePointToDate(std::chrono::system_clock::time_point date);
    QDate timePointTQDate(std::chrono::system_clock::time_point date);
    std::chrono::system_clock::time_point  getLaterTimeFromNow(int days);
    std::chrono::system_clock::time_point nextDayAfterTime(std::chrono::system_clock::time_point, int reqDay);
    int daysInMonth(int month, int year);
}

#endif // TIMEUTILS_H
