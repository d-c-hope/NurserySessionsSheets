#include "sessionsreader.h"
#include "timeutils.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>


SessionsReader::SessionsReader()
{
}



void SessionsReader::writeSessions(sessionsMap sessionsM, std::string filename) {
    std::ofstream out("/Users/david_hope2/Desktop/tmp/sessionsList.txt");
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



//std::vector<int> v2;
//    std::vector<int> v3;

//    bool toggle = false;
//    std::partition_copy(v1.begin(),
//                        v1.end(),
//                        std::back_inserter(v2),
//                        std::back_inserter(v3),
//                        [&toggle](int) { return toggle = !toggle; });




// 22, 29/08/2015, MonAM, Tue_AM, Thu_PM,

sessionsMap SessionsReader::readSessions(std::string filename)
{
    if (SessionsReader::sessionsM.size() > 0) return SessionsReader::sessionsM;
    sessionsMap sessionsM;

    std::vector<std::string> lines;
    std::ifstream in("/Users/david_hope2/Desktop/tmp/sessionslist.txt");
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
//        boost::algorithm::trim(strs[1]);
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


//void ChildListReader::writeList(std::vector<Child> children, std::string filename) {
//    std::ofstream out("/Users/david_hope2/Desktop/tmp/childlistOut.txt");
//    for (auto child: children) {
//        std::string dob = TimeUtils::timePointDateToString(child.dob);
//        // David, Hope, 20/03/2012
//        out << child.id << ", " << child.firstName << ", "  << child.lastName << ", " << dob << "\n";
//    }
//}








    //        std::string monAMStr = strs[4];
    //        std::string monPMStr = strs[6];
    //        std::string tueAMStr = strs[8];
    //        std::string tuePMStr = strs[10];
    //        std::string wedAMStr = strs[12];
    //        std::string wedPMStr = strs[14];
    //        std::string thuAMStr = strs[16];
    //        std::string thuPMStr = strs[18];
    //        std::string friAMStr = strs[20];
    //        std::string friPMStr = strs[22];


    //      std::cout << strs[0] << "*";
    //      struct tm tm;
    //      memset(&tm, 0, sizeof(struct tm));
    //      strptime(strs[6].c_str(), "%d\/%m\/%Y", &tm);
    //      auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    //      std::time_t t = std::chrono::system_clock::to_time_t(tp);
    //      std::cout << std::put_time(std::localtime(&t), "%d/%m/%Y") << '\n';
    //      std::chrono::system_clock::time_point age = tp;
