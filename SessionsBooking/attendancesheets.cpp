#include "attendancesheets.h"
#include "sessionsreader.h"
#include "child.h"
#include "timeutils.h"
#include "childWeeklySessions.h"
#include "appConstants.h"
#include "apputils.h"

#include <chrono>
#include <list>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std::chrono;



MonthDetails::MonthDetails(std::tuple<ChildList,ChildList, ChildList> childrenByRoom, std::map<int, ChildWeeklySessions> sessionsThisMonth) {
    this->childrenByRoom = childrenByRoom;
    this->sessionsThisMonth = sessionsThisMonth;
}


bool sortFunc(Child c1, Child c2) { return (c1.dob < c2.dob); }


// sorted children = sort(children, bydob)
// loop over the months
//      calculate timepoints for start and end of the month
//      Loop over the children
//          loop over the child's sessions
//              add child to month if there are sessions that overlap this month
//              pick the room
std::vector<std::string> AttendanceSheets::createSheets(std::vector<Child> children, MonthRange monthRange) {
    SessionsReader sessionsReader;
    sessionsMap sessionsM = sessionsReader.readSessions();
    std::vector<std::string> sheets;

    std::sort(children.begin(), children.end(), sortFunc);
    for (int i = monthRange.startYear; i <= monthRange.endYear; i++) {
        int endMonth = 12;
        if (monthRange.startYear == monthRange.endYear) endMonth = monthRange.endMonth;
        for (int j = monthRange.startMonth; j <= endMonth; j++) {
            MonthDetails monthDetails = AttendanceSheets::createSheetsForMonth(j, i, children, sessionsM);
            std::string poohsText = AttendanceSheets::getSheetsTextForRoom(std::get<0>(monthDetails.childrenByRoom), monthDetails.sessionsThisMonth);
            std::string pigletsText = AttendanceSheets::getSheetsTextForRoom(std::get<1>(monthDetails.childrenByRoom), monthDetails.sessionsThisMonth);
            std::string tiggersText = AttendanceSheets::getSheetsTextForRoom(std::get<2>(monthDetails.childrenByRoom), monthDetails.sessionsThisMonth);
            std::string sheetText = "Poohs and Roohs\n" + poohsText + "\n\n" + "Piglets\n" + pigletsText + "\n\n" +
                    "Tiggers\n" + tiggersText;
            sheets.push_back(sheetText);
        }
    }
    return sheets;

}


MonthDetails AttendanceSheets::createSheetsForMonth(int month, int year, std::vector<Child> children, sessionsMap allChildrensSessions) {

    system_clock::time_point startOfMonth = TimeUtils::dateToTimePoint(1, month, year);
    int daysInMonth = TimeUtils::daysInMonth(month, year);
    system_clock::time_point endOfMonth = TimeUtils::dateToTimePoint(daysInMonth, month, year);

    std::vector<Child> childrenInNursery;
    std::map<int, ChildWeeklySessions> sessionsThisMonth;

    for (auto child: children) {
        if (AttendanceSheets::childHasSession(child, startOfMonth, endOfMonth, allChildrensSessions)) {
            childrenInNursery.push_back(child);
            ChildWeeklySessions sessions = AttendanceSheets::pickSessionSet(child, startOfMonth, endOfMonth, allChildrensSessions);
            sessionsThisMonth[child.id] = sessions;

        }
    }

    std::tuple<ChildList,ChildList, ChildList> childrenByRoom = assignToRooms(childrenInNursery, month, year);
    MonthDetails monthDetails(childrenByRoom, sessionsThisMonth);

    return monthDetails;
}


bool AttendanceSheets::childHasSession(Child child, system_clock::time_point startOfMonth,
                     system_clock::time_point endOfMonth, sessionsMap allChildrensSessions) {

    if ( allChildrensSessions.find(child.id) == allChildrensSessions.end() ) return false;

    bool retVal = false;
    std::vector<ChildWeeklySessions> childWSList = allChildrensSessions[child.id];
    for (auto weeklySessions: childWSList) {
        if ( (weeklySessions.startDate <= startOfMonth) && (weeklySessions.endDate > startOfMonth) ) retVal = true;
        if ( (weeklySessions.startDate >= startOfMonth) && (weeklySessions.startDate <= endOfMonth) ) retVal = true;
    }

    return retVal;

}

// Spec:
// If a child changes sessions in a month use the new sessions if they change before the 15th and the old sessions if they change on the 15th or after.
// Actual:
// There might be more than one change in a month, e.g. first week then second week. So we pick the last one before the fifteenth
// We assume there is one valid session set otherwise we would not have got into this method
ChildWeeklySessions AttendanceSheets::pickSessionSet(Child child, system_clock::time_point startOfMonth,
                     system_clock::time_point endOfMonth, sessionsMap allChildrensSessions) {

    ChildWeeklySessions currentSessionSet;// = null;
    std::vector<ChildWeeklySessions> validChildWSList;

    std::vector<ChildWeeklySessions> childWSList = allChildrensSessions[child.id];
    for (auto weeklySessions: childWSList) {

        if ( (weeklySessions.startDate <= startOfMonth) && (weeklySessions.endDate > startOfMonth) ) validChildWSList.push_back(weeklySessions);
        else if ( (weeklySessions.startDate >= startOfMonth) && (weeklySessions.startDate <= endOfMonth) ) validChildWSList.push_back(weeklySessions);
    }

    currentSessionSet = validChildWSList[0];
    system_clock::time_point fifteenth = startOfMonth + std::chrono::hours(24*15);
    for (auto weeklySessions: validChildWSList) {
        if (weeklySessions.startDate < fifteenth) currentSessionSet = weeklySessions;
    }

    return currentSessionSet;

}



//All children under 2 or becoming 2 in the second half of the month should be shown in Poohs and Roos
//4. All children aged 2 or becoming 2 in the first half of the month or becoming 3 in the 2nd half of the month should be in Piglets.
//5. All children over 3 or becoming 3 in the first half of the month should be in Tiggers and Christopher Robins

std::tuple<ChildList,ChildList, ChildList> AttendanceSheets::assignToRooms(std::vector<Child> childrenInNursery, int month, int year) {
//    std::tuple<ChildList,ChildList, ChildList, ChildList> listsByRoom;
    ChildList poosRoos;
    ChildList piglets;
    ChildList tiggers;

    for (auto child: childrenInNursery) {
        // Get middle of month
        int daysInMonth = TimeUtils::daysInMonth(month, year);
        system_clock::time_point middleOfMonth = TimeUtils::dateToTimePoint(daysInMonth/2, month, year);

        int ageOnDate = getAgeOnDate(child.dob, middleOfMonth);
        if (ageOnDate < 2) poosRoos.push_back(child);
        else if (ageOnDate < 3) piglets.push_back(child);
        else tiggers.push_back(child);

    }

    auto listsByRooms = std::make_tuple (poosRoos, piglets, tiggers);
    return listsByRooms;
}


int AttendanceSheets::getAgeOnDate(system_clock::time_point dob, system_clock::time_point date) {
    auto dobTuple = TimeUtils::timePointToDate(dob);
    auto dateTuple = TimeUtils::timePointToDate(date);
    int years = std::get<0>(dateTuple) - std::get<0>(dobTuple);
    int months = std::get<1>(dateTuple) - std::get<1>(dobTuple);
    int days = std::get<2>(dateTuple) - std::get<2>(dobTuple);

    // examples
    // dob     , date
    // feb 2013, may 2013
    // march 2013, jan 2014
    // march 2013, march 2014
    if (months < 0) years -= 1;
    else if (months == 0) {
        if (days < 0) years -= 1;
    }

    return years;
}


std::list<Child> AttendanceSheets::getChildrenInOnDay(std::vector<Child> children,
                                                      std::map<int, ChildWeeklySessions> sessionsForMonth,
                                                      std::string day) {

    std::list<Child> childrenInOnDay;
    for (auto child: children) {
        ChildWeeklySessions childSessions = sessionsForMonth[child.id];
        if (std::find(childSessions.sessionsList.begin(), childSessions.sessionsList.end(), day)
                != childSessions.sessionsList.end()) {
            childrenInOnDay.push_back(child);
        }
    }
    return childrenInOnDay;
}


std::string AttendanceSheets::getSheetsTextForRoom(std::vector<Child> children, std::map<int, ChildWeeklySessions> sessionsForMonth) {

    std::list<Child> monAmChildren = AttendanceSheets::getChildrenInOnDay(children, sessionsForMonth, "monAM");
    std::list<Child> monPmChildren = AttendanceSheets::getChildrenInOnDay(children, sessionsForMonth, "monPM");
    std::list<Child> tueAmChildren = AttendanceSheets::getChildrenInOnDay(children, sessionsForMonth, "tueAM");
    std::list<Child> tuePmChildren = AttendanceSheets::getChildrenInOnDay(children, sessionsForMonth, "tuePM");
    std::list<Child> wedAmChildren = AttendanceSheets::getChildrenInOnDay(children, sessionsForMonth, "wedAM");
    std::list<Child> wedPmChildren = AttendanceSheets::getChildrenInOnDay(children, sessionsForMonth, "wedPM");
    std::list<Child> thuAmChildren = AttendanceSheets::getChildrenInOnDay(children, sessionsForMonth, "thuAM");
    std::list<Child> thuPmChildren = AttendanceSheets::getChildrenInOnDay(children, sessionsForMonth, "thuPM");
    std::list<Child> friAmChildren = AttendanceSheets::getChildrenInOnDay(children, sessionsForMonth, "friAM");
    std::list<Child> friPmChildren = AttendanceSheets::getChildrenInOnDay(children, sessionsForMonth, "friPM");

    std::vector<std::list<Child>> allDays = {monAmChildren, monPmChildren, tueAmChildren, tuePmChildren,
                                                      wedAmChildren, wedPmChildren, thuAmChildren, thuPmChildren,
                                                      friAmChildren, friPmChildren};
    std::stringstream ss;
    bool anyLeft = false;
    for (auto halfDayList: allDays) if (halfDayList.size() > 0) anyLeft = true;

    int paddedLength = 20;
    std::string empty = "";
    empty.insert(empty.begin(), paddedLength, ' ');


    std::vector<std::string> days{"MonAM", "MonPM","TueAM", "TuePM", "WedAM", "WedPM", "ThuAM", "ThuPM", "FriAM", "FriPM"};
    for (auto& d: days) {
        if (d.size() < paddedLength) d.insert(d.end(), paddedLength-d.size(), ' ');
    }
    std::string daysJoined = AppUtils::join<std::string>(days, ", ");
    ss << daysJoined << std::endl;

    while(anyLeft) {

        std::vector<std::string> entries;

        anyLeft = false;
        for (auto& halfDayList: allDays) {
            if (halfDayList.size() > 0) {
                auto child = halfDayList.front();
                std::string name = child.firstName + " " + child.lastName;
                if (name.size() < paddedLength) name.insert(name.end(), paddedLength-name.size(), ' ');

                entries.push_back(name);
                halfDayList.pop_front();
            }
            else {
                entries.push_back(empty);
            }

            if (halfDayList.size() > 0) anyLeft = true;
        }
        std::string joined = AppUtils::join<std::string>(entries, ", ");
        ss << joined << std::endl;
    }
    return ss.str();

}









