#include "sessionshelpers.h"

SessionsHelpers::SessionsHelpers()
{
}


sessionsMap SessionsHelpers::filterOldSessions(sessionsMap sessionsM, int olderThanInDays) {
    sessionsMap filteredMap;
    for (auto childWeeklySessionsKV: sessionsM) {
        std::vector<ChildWeeklySessions> filtered = filterOldSessionsPerChild(childWeeklySessionsKV.second, olderThanInDays);
        if (filtered.size() > 0) filteredMap[childWeeklySessionsKV.first] = filtered;
    }
    return filteredMap;
}


std::vector<ChildWeeklySessions> SessionsHelpers::filterOldSessionsPerChild(std::vector<ChildWeeklySessions> childWeeklySessionsList, int olderThanInDays) {
    std::chrono::system_clock::time_point xDaysAgo = std::chrono::system_clock::now() - std::chrono::hours(24*olderThanInDays);
    std::vector<ChildWeeklySessions> filteredList;

    for (auto weeklySessions: childWeeklySessionsList) {
        if (weeklySessions.endDate > xDaysAgo) filteredList.push_back(weeklySessions);
    }
    return filteredList;
}


//ChildWeeklySessions SessionsForm::getCurrentSessions(std::vector<ChildWeeklySessions> childWeeklySessionsList) {
//    ChildWeeklySessions current; //= childWeeklySessionsList[0];
//    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
//    for (auto weeklySessions: childWeeklySessionsList) {
//        if (weeklySessions.startDate < now) current = weeklySessions;
//    }
//    return current;
//}


//ChildWeeklySessions SessionsForm::getNextSessions(std::vector<ChildWeeklySessions> childWeeklySessionsList) {
//    ChildWeeklySessions next;// = childWeeklySessionsList[0];
//    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
//    for (auto weeklySessions: childWeeklySessionsList) {
//        if (weeklySessions.startDate > now) {
//            next = weeklySessions;
//            break;
//        }
//    }
//    return next;
//}
