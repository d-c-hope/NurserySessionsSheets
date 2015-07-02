#ifndef SESSIONSREADER_H
#define SESSIONSREADER_H


#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "sessions.h"


typedef std::map<int, std::vector<Sessions>> sessionsMap;


class SessionsReader
{
public:
    SessionsReader();
    sessionsMap readSessions(std::string filename);
    void writeSessions(sessionsMap sessionsM, std::string filename);

private:
    static sessionsMap sessionsM;

};

#endif // SESSIONSREADER_H
