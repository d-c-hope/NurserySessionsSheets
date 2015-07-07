#ifndef SESSIONSHELPERS_H
#define SESSIONSHELPERS_H

#include <vector>
#include <sessionsreader.h>
#include <childWeeklySessions.h>

class SessionsHelpers
{
public:
    SessionsHelpers();
    static sessionsMap filterOldSessions(sessionsMap sessionsM, int olderThanInDays);
    static std::vector<ChildWeeklySessions> filterOldSessionsPerChild(std::vector<ChildWeeklySessions> childWeeklySessionsList,
                                                                      int olderThanInDays);
};

#endif // SESSIONSHELPERS_H
