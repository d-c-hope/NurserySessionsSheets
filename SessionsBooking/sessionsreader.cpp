#include "sessionsreader.h"
#include "timeutils.h"
#include "appConstants.h"

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

SessionsReader::SessionsReader()
{
}



void SessionsReader::writeSessions(sessionsMap sessionsM) {

    std::string filename = AppConstants::defaultChildListFile;
    if (! exists(AppConstants::appFilesDir)) {
        create_directory(AppConstants::appFilesDir);
    }

    std::ofstream out(AppConstants::defaultSessionsFile);
    for (auto& kv : sessionsM) {
        for (auto sessionSet: kv.second) {
            std::string startDate = TimeUtils::timePointDateToString(sessionSet.startDate);
            std::string endDate = TimeUtils::timePointDateToString(sessionSet.endDate);
            out << sessionSet.childId << ", " << startDate << ", " << endDate << ", ";
            std::stringstream listStrStr;
            auto sTimes = sessionSet.sessionsList;
            std::copy(sTimes.begin(), sTimes.end(), std::ostream_iterator<std::string>(listStrStr, ","));
            std::string listStr = listStrStr.str();
            listStr.pop_back();
            out << listStr << std::endl;
        }
    }
    SessionsReader::sessionsM = sessionsM;
}



// 22, 29/08/2015, MonAM, Tue_AM, Thu_PM,

sessionsMap SessionsReader::readSessions()
{
    if (SessionsReader::sessionsM.size() > 0) return SessionsReader::sessionsM;
    sessionsMap sessionsM;

    std::vector<std::string> lines;
    std::ifstream in(AppConstants::defaultSessionsFile);
    if(in.fail()) {
        return sessionsM;
    }

    char buf[300];
    while( in.getline(buf, 300) ) {
        lines.push_back(std::string(buf));
    }

    for (auto line: lines) {
        ChildWeeklySessions childSessions;

        std::vector<std::string> strs;

        boost::split(strs, line, boost::is_any_of(","));
        for (auto& fieldStr: strs) {
            boost::algorithm::trim(fieldStr);
        }
        int childId = atoi(strs[0].c_str());
        std::string dateStr = strs[1];
        std::string endDateStr = strs[2];
        childSessions.childId = childId;
        childSessions.startDate = TimeUtils::timeStrToTimePointDate(dateStr);
        childSessions.endDate = TimeUtils::timeStrToTimePointDate(endDateStr);

        std::copy( strs.begin()+3, strs.end(), std::back_inserter(childSessions.sessionsList) );

        if ( sessionsM.find(childId) != sessionsM.end() ) {
            sessionsM[childId].push_back(childSessions);
        } else {
            std::vector<ChildWeeklySessions> cSessionsList{childSessions};
            sessionsM[childId] = std::vector<ChildWeeklySessions>{childSessions};
        }

    }

    return sessionsM;

}




sessionsMap SessionsReader::sessionsM;



