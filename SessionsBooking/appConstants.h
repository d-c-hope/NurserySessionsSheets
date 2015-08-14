#ifndef APP_CONSTANTS_H
#define APP_CONSTANTS_H

#include <string>
#include <QStandardPaths>



namespace AppConstants {

using namespace std;
    const string homeDir = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0].toStdString();
    const string appFilesDir = homeDir + "/NurserySessionsApp";
    const string defaultChildListFile = appFilesDir + "/childlist.txt";
    const string defaultSessionsFile = appFilesDir + "/sessionslist.txt";
    const string defaultMonthFilePrefix = homeDir + "/Desktop/sessions_for_";

//    const string defaultChildListFile = QStandardPaths::HomeLocation.toStdString(); ///Users/david_hope2/Desktop/tmp/childlist.txt";
//    const string defaultSessionsFile = "/Users/david_hope2/Desktop/tmp/sessionslist.txt";
//    const string defaultMonthFilePrefix = "/Users/david_hope2/Desktop/tmp/sessions_for_";

}

#endif // APP_CONSTANTS_H
