#include "childlistexporter.h"
#include "timeutils.h"
#include "attendancesheets.h"
#include "apputils.h"

using namespace std;
using namespace std::chrono;


ChildListExporter::ChildListExporter(vector<Child> children) {
    this->children = children;
}



//bool sortFunc(Child c1, Child c2) { return (c1.dob < c2.dob); }


//void ChildListExporter::exportList(string filename) {


//    vector<Child> monthDisplacedChildren;
//    for (auto child: children) {
//        child.dob = add4Months(child.dob);
//        monthDisplacedChildren.push_back(child);
//    }
//    sort(monthDisplacedChildren.begin(), monthDisplacedChildren.end(), sortFunc);
//    vector<string> lines;

//    int paddedLength = 25;
//    for (auto current: monthDisplacedChildren) {
//        string name = current.firstName + " " + current.lastName;
//        if (name.size() < paddedLength) name.insert(name.end(), paddedLength-name.size(), ' ');
//        string dobStr = TimeUtils::timePointDateToString(current.dob);
//        lines.push_back(name + " " + dobStr);
//    }

////    for (auto line: lines) {
////        for (string item: line) {
////            if (item.size() < paddedLength) item.insert(item.end(), paddedLength-name.size(), ' ');
////        }
////    }

//    string joined = AppUtils::join<string>(lines, "\n");
//    cout << joined;


//}



void ChildListExporter::exportList(string filename) {

    stringstream sheet;
    int paddedLength = 25;

    vector<Child> sortedChildren = children;
    sort(sortedChildren.begin(), sortedChildren.end(), sortFunc);

    Child youngest = sortedChildren[0];
    auto youngestDate = TimeUtils::timePointToDate(youngest.dob);
    int year = get<2>(youngestDate);
    int month = get<1>(youngestDate);
    if (month < 9) year -= 1;
    int prevMonth = month;
    int prevYear = year;

    sheet << year << "\n";
    for (Child child: sortedChildren) {

        auto dob = TimeUtils::timePointToDate(child.dob);
        year = get<0>(dob);
        month = get<1>(dob);
        if ( ((prevMonth < 9) && (month >= 9)) ||
             ((prevMonth < 9) && (year  > prevYear)) ) {
            sheet << "\n\n" << year << endl;
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
    cout << childListStr;


//    vector<string> lines;

//    int paddedLength = 25;
//    for (auto current: monthDisplacedChildren) {
//        string name = current.firstName + " " + current.lastName;
//        if (name.size() < paddedLength) name.insert(name.end(), paddedLength-name.size(), ' ');
//        string dobStr = TimeUtils::timePointDateToString(current.dob);
//        lines.push_back(name + " " + dobStr);
//    }

////    for (auto line: lines) {
////        for (string item: line) {
////            if (item.size() < paddedLength) item.insert(item.end(), paddedLength-name.size(), ' ');
////        }
////    }

//    string joined = AppUtils::join<string>(lines, "\n");
//    cout << joined;


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


//        Child current = children[0];
//        std::tuple<int, int, int> dobTuple = timePointToDate(current.dob);

//        int month = std::get<1>(dobTuple);
//        if (month < 10) month = month + 4;
//        std::rotate(v.begin(), v.begin() + 1, v.end());

//    for (int month = 1; month < 13; month++) {

//    }


//    std::sort(children.begin(), children.end(), sortFunc);
