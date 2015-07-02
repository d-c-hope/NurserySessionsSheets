#include "timeutils.h"
#include <sstream>
#include <chrono>
#include <iomanip>
#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>



namespace TimeUtils {

    std::string  timePointDateToString(std::chrono::system_clock::time_point date) {
        std::stringstream s;
        std::time_t dateT = std::chrono::system_clock::to_time_t(date);
        s << std::put_time(std::localtime(&dateT), "%d/%m/%Y");
        return s.str();
    }


    std::chrono::system_clock::time_point timeStrToTimePointDate(std::string timeStr) {
        struct tm tm;
        memset(&tm, 0, sizeof(struct tm));
        strptime(timeStr.c_str(), "%d\/%m\/%Y", &tm);
        auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

        return tp;
//        std::time_t t = std::chrono::system_clock::to_time_t(tp);
//        std::cout << std::put_time(std::localtime(&t), "%d/%m/%Y") << '\n';
//        std::chrono::system_clock::time_point age = tp;
    }


    // day is 1-31, month is 1-12, year is year like 2015
    std::chrono::system_clock::time_point  qdateToTimePoint(int day, int month, int year) {

        struct std::tm tm;
        memset(&tm, 0, sizeof(struct tm));
        tm.tm_year = year - 1900;
        tm.tm_mon = month-1;
        tm.tm_mday = day;
        auto dateTp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

        return dateTp;
    }


    std::vector<int> getYears() {
        // get the year now
        std::vector<int> yearsI;
        auto timeNow = std::chrono::system_clock::now();
        time_t tt = std::chrono::system_clock::to_time_t(timeNow);
        tm utc_tm = *gmtime(&tt);
        int yearNow = utc_tm.tm_year + 1900;

        boost::push_back(yearsI, boost::irange(yearNow-6, yearNow+1));

        return yearsI;
    }

}
