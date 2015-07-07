#include "timeutils.h"
#include <sstream>
#include <chrono>
#include <iomanip>
#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>


//struct tm {
//   int tm_sec;         /* seconds,  range 0 to 59          */
//   int tm_min;         /* minutes, range 0 to 59           */
//   int tm_hour;        /* hours, range 0 to 23             */
//   int tm_mday;        /* day of the month, range 1 to 31  */
//   int tm_mon;         /* month, range 0 to 11             */
//   int tm_year;        /* The number of years since 1900   */
//   int tm_wday;        /* day of the week, range 0 to 6    */
//   int tm_yday;        /* day in the year, range 0 to 365  */
//   int tm_isdst;       /* daylight saving time             */
//};



namespace TimeUtils {

    using namespace std::chrono;

    std::string timePointDateToString(std::chrono::system_clock::time_point date) {
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

    }


    QDate timePointTQDate(std::chrono::system_clock::time_point date) {
        std::time_t dateT = std::chrono::system_clock::to_time_t(date);
        std::tm* tm = std::localtime(&dateT);
        QDate retDate(tm->tm_year+1900, tm->tm_mon, tm->tm_mday);
        return retDate;
    }


    // day is 1-31, month is 1-12, year is year like 2015
    std::chrono::system_clock::time_point  dateToTimePoint(int day, int month, int year) {

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


    std::chrono::system_clock::time_point  getLaterTimeFromNow(int days) {
        std::chrono::system_clock::time_point futureT = std::chrono::system_clock::now() + std::chrono::hours(24*days);
        return futureT;
    }


//    time_point nextMondayAfterTime(time_point) {
//        std::time_t dateT = std::chrono::system_clock::to_time_t(date);
//        std::tm tm = std::localtime(&dateT);
//        int dayOfWeek = tm.tm_wday;
//        int change;
//        if (dayOfWeek <= 1) change = 1 - dayOfWeek;
//        else mon = dayOfWeek + (6 - dayOfWeek)

//    }


    // reqDay is 0-6 where 0 is sunday
    system_clock::time_point nextDayAfterTime(system_clock::time_point date, int reqDay) {
        std::time_t dateT = std::chrono::system_clock::to_time_t(date);
        std::tm tm = *std::localtime(&dateT);
        int dayOfWeek = tm.tm_wday;
        int change;
        if (dayOfWeek <= reqDay) change = reqDay - dayOfWeek;
        else change = (dayOfWeek - reqDay) + 7;
        return system_clock::now() + std::chrono::hours(24*change);
    }

}
