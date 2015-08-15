#include "childlistreader.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <boost/filesystem.hpp>

#include "child.h"
#include "timeutils.h"
#include <appConstants.h>


using namespace boost::filesystem;


ChildListReader::ChildListReader()
{
}


std::vector<Child> ChildListReader::readList()
{
    std::vector<std::string> lines;
    std::vector<Child> children;
    std::ifstream in(AppConstants::defaultChildListFile);
    if(in.fail()) {
        return children;
    }

    char buf[200];
    while(in.getline(buf, 200)) {
        lines.push_back(std::string(buf));
    }


    for (auto line: lines) {
        std::vector<std::string> strs;
        boost::split(strs, line, boost::is_any_of(", "));
      struct tm tm;
      memset(&tm, 0, sizeof(struct tm));

      strptime(strs[6].c_str(), "%d\/%m\/%Y", &tm);
      auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

      std::time_t t = std::chrono::system_clock::to_time_t(tp);
      std::chrono::system_clock::time_point age = tp;

      int id = atoi(strs[0].c_str());

      Child child(id, strs[2], strs[4], age);
      children.push_back(child);
    }

    return children;


}





void ChildListReader::writeList(std::vector<Child> children) {
    std::string filename = AppConstants::defaultChildListFile;
    if (! exists(AppConstants::appFilesDir)) {
        create_directory(AppConstants::appFilesDir);
    }

    std::ofstream out(filename);
    for (auto child: children) {
        std::string dob = TimeUtils::timePointDateToString(child.dob);
        // David, Hope, 20/03/2012
        out << child.id << ", " << child.firstName << ", "  << child.lastName << ", " << dob << "\n";
    }
}













