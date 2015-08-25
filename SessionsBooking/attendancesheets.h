#ifndef ATTENDANCESHEETS_H
#define ATTENDANCESHEETS_H

#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <child.h>
#include "sessionsreader.h"
#include <chrono>
#include <monthrange.h>

//typedef std::tuple<Child, int, std::string> ChildAgeRoom;
typedef std::vector<Child> ChildList;

class MonthDetails {
public:
    std::tuple<ChildList,ChildList, ChildList> childrenByRoom;
    std::map<int, ChildWeeklySessions> sessionsThisMonth;

    MonthDetails(std::tuple<ChildList,ChildList, ChildList> childrenByRoom, std::map<int, ChildWeeklySessions> sessionsThisMonth);
};

bool sortFunc(Child c1, Child c2);

namespace AttendanceSheets {

    using namespace std::chrono;

    std::vector<std::string> createSheets(std::vector<Child> children, MonthRange monthRange, bool isSepSheets);

    MonthDetails createSheetsForMonth(int month, int year, std::vector<Child> children, sessionsMap allChildrensSessions);

    bool childHasSession(Child child, system_clock::time_point startOfMonth,
                         system_clock::time_point endOfMonth, sessionsMap allChildrensSessions);

    std::tuple<ChildList,ChildList, ChildList> assignToRooms(std::vector<Child> childrenInNursery, int month, int year);

    int getAgeOnDate(system_clock::time_point dob, system_clock::time_point date);

    ChildWeeklySessions pickSessionSet(Child child, system_clock::time_point startOfMonth,
                         system_clock::time_point endOfMonth, sessionsMap allChildrensSessions);

    std::list<Child> getChildrenInOnDay(std::vector<Child> children,
                                          std::map<int, ChildWeeklySessions> sessionsForMonth,
                                          std::string day);

    std::string getSheetsTextForRoom(std::vector<Child> children, std::map<int, ChildWeeklySessions> sessionsForMonth,
                                     bool isDaysHeader);
}


#endif // ATTENDANCESHEETS_H
