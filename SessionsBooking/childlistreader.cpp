#include "childlistreader.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <ctime>
#include <chrono>
#include <iomanip>

#include "child.h"

ChildListReader::ChildListReader()
{
}

std::vector<Child> ChildListReader::readList(std::string filename)
{
    std::vector<std::string> lines;
    std::ifstream in("/Users/david_hope2/Desktop/tmp/childlist.txt");
    char buf[200];
    while(in.getline(buf, 200)) {
        lines.push_back(std::string(buf));
//        std::cout << buf << std::endl;
    }

    std::vector<Child> children;
    for (auto line: lines) {
        std::vector<std::string> strs;
        boost::split(strs, line, boost::is_any_of(", "));

      std::cout << strs[0] << "*";


//      std::tm tm;
      struct tm tm;
      memset(&tm, 0, sizeof(struct tm));



//      std::stringstream ss(/*strs[4]*/);
//      ss >> std::get_time(&tm, "%d/%m/%Y");
      strptime(strs[4].c_str(), "%d\/%m\/%Y", &tm);
//      strptime("2001-11-12", "%Y-%m-%d", &tm);

      auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

//      char timeStr[10];
//      std::size_t strftime( strs[4], std::size_t count, "%d/%m/%Y", /*const std::tm* time*/ );
//      auto t = std::time(nullptr);
//      auto tm = *std::localtime(&t);
      std::time_t t = std::chrono::system_clock::to_time_t(tp);
      std::cout << std::put_time(std::localtime(&t), "%d/%m/%Y") << '\n';


//      std::cout << tp << std::endl;



//    try {
      std::chrono::system_clock::time_point age = tp;
//        int age = boost::lexical_cast<int>( strs[4] );
//    } catch( boost::bad_lexical_cast const& ) {
//        std::cout << "Error: input string was not valid" << std::endl;
//    }
        Child child(strs[0], strs[2], age);
//        std::cout << strs[1] << "*";
//        std::cout << strs[2] << "*";
//        std::cout << strs[3] << "*";
//        std::cout << strs[4] << "*";
//        std::cout << std::endl;
        children.push_back(child);
    }

    return children;


}
