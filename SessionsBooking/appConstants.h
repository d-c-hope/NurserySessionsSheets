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
    const string defaultChildExport = homeDir + "/Desktop/childListExport.txt";

    const bool sepFiles = true;

    // Note that we use a comma for delimiting with separate sheets, and a tab if not. This is simply to support apple iwork - you can drag a comma
    // separated file over a spreadsheet or you can copy and paste in a tab separated file, but not the other way round
    const string delimiter = ", ";

}

#endif // APP_CONSTANTS_H
