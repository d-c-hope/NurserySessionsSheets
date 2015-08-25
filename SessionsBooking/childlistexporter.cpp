#include "childlistexporter.h"
#include "timeutils.h"
#include "attendancesheets.h"
#include "apputils.h"

using namespace std;
using namespace std::chrono;


ChildListExporter::ChildListExporter(vector<Child> children) {
    this->children = children;
}


string ChildListExporter::exportList(string filename) {

    stringstream sheet;
    int paddedLength = 25;

    vector<Child> sortedChildren = children;
    sort(sortedChildren.begin(), sortedChildren.end(), sortFunc);

    Child youngest = sortedChildren[0];
    auto youngestDate = TimeUtils::timePointToDate(youngest.dob);
    int year = get<0>(youngestDate);
    int month = get<1>(youngestDate);
    if (month < 9) year -= 1;
    int prevMonth = month;
    int prevYear = year;

    sheet << "Sept " << year << "\n";
    for (Child child: sortedChildren) {

        auto dob = TimeUtils::timePointToDate(child.dob);
        year = get<0>(dob);
        month = get<1>(dob);
        if ( ((prevMonth < 9) && (month >= 9)) ||
             ((prevMonth < 9) && (year  > prevYear)) ) {

            // must be careful if we jump to next year but are in the year starting previous september
            if (month < 9) sheet << "\n\nSept " << year -1 << endl;
            else sheet << "\n\nSept " << year << endl;
        }

        else if ( year  > prevYear) {
            sheet << string(40, '-') << endl;
        }

        else if ( (prevMonth < 4) && (month >= 4) ) {
            sheet << string(40, '-') << endl;
        }

        string name = child.firstName + " " + child.lastName;
        if (name.size() < paddedLength) name.insert(name.end(), paddedLength-name.size(), ' ');
        string dobStr = TimeUtils::timePointDateToString(child.dob);
        string line = name + " " + dobStr;
        sheet << line << endl;

        prevMonth = month;
        prevYear = year;

    }

    string childListStr = sheet.str();

    return childListStr;
}


system_clock::time_point ChildListExporter::add4Months(system_clock::time_point date) {
    std::time_t dateT = std::chrono::system_clock::to_time_t(date);
    std::tm tm = *std::localtime(&dateT);
    // indexed from 0
    int month = tm.tm_mon;
    if (month < 8) month += 4;
    system_clock::time_point newDate = TimeUtils::dateToTimePoint(tm.tm_mday, month, tm.tm_year+1900);

    return newDate;
}






