#ifndef SESSIONSREADER_H
#define SESSIONSREADER_H


#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "childWeeklySessions.h"


typedef std::map<int, std::vector<ChildWeeklySessions>> sessionsMap;


class SessionsReader
{
public:
    SessionsReader();
    sessionsMap readSessions();
    void writeSessions(sessionsMap sessionsM);

private:
    static sessionsMap sessionsM;

};

#endif // SESSIONSREADER_H
