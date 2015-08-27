#include <QMessageBox>
#include <QString>
#include <sstream>

#include "sessionsform.h"
#include "ui_sessionsform.h"
#include "sessionsreader.h"
#include "timeutils.h"
#include "sessionshelpers.h"


std::string headerPrefix = "Weekly sessions for ";
std::string subHeadMain = R"(These are the standard weekly sessions for a child.
If there are changes for a single week you can add these in temp sessions";
and if the regulation sessions are due to change you can add these in new sessions)";

std::string subHeadNew = R"(These wll become the standard weekly sessions starting
from the week specified below)";

std::string subHeadTemp = R"(These are one off changes toa child's sessions
They only apply for a single week starting at the specified date)";

std::string subHeadTemp2 = "These are one off changes toa child's sessions";



SessionsForm::SessionsForm(Child child, QWidget *parent, PageNavigator* _navigator) :
    StackWidget(parent),
    ui(new Ui::SessionsForm)
{
    ui->setupUi(this);
    navigator = _navigator;

    this->child = child;

    saveButton = ui->saveButton;
    cancelButton = ui->cancelButton;
    newSessionsButton = ui->newSessionsButton;
    prevSessionsButton = ui->prevSessionsButton;
    startDateEdit = ui->dateEdit;
    endDateEdit = ui->endDateEdit;

    titleTextLabel = ui->titleText;
    subTitleTextLabel = ui->subTitleText;

    std::string titleText = headerPrefix + child.firstName + " " + child.lastName;
    titleTextLabel->setText(QString::fromStdString(titleText));

    viewType = CURRENT;

    connect(saveButton, SIGNAL ( clicked() ), this, SLOT ( onSaveClicked() ) );
    connect(cancelButton, SIGNAL ( clicked() ), this, SLOT ( onCancelClicked() ) );
    connect(newSessionsButton, SIGNAL ( clicked() ), this, SLOT ( onNewSessionsClicked() ) );
    connect(prevSessionsButton, SIGNAL ( clicked() ), this, SLOT ( onPrevSessionsClicked() ) );

    startDateEdit->setDate(QDate::currentDate());
    endDateEdit->setDate(QDate::currentDate());

    SessionsReader sessionsReader;
    sessionsM = sessionsReader.readSessions();
    sessionsM = SessionsHelpers::filterOldSessions(sessionsM, 31);
    sessionsReader.writeSessions(sessionsM);
    doInitialLoadFromMap(sessionsM);

    isOnCurrent = true;

    updatePageLabel();
}


void SessionsForm::updatePageLabel() {
    std::stringstream text("Page ");
    text << currentIndex+1 << " of " << listOfWeeklySessions.size();
    ui->pageLabel->setText(QString::fromStdString(text.str()));
}


void SessionsForm::onCancelClicked() {
    navigator->goBack();
}


void SessionsForm::onNewSessionsClicked() {

    bool isUpdated = updateWithWarningDialog();
    if (! isUpdated) return;

    // Doesn't apply if index is 0 which is fine - don't want more pages if nothing on current one
    // Though possible user wants to add one set then another in one go - TODO look at this
    if (currentIndex == listOfWeeklySessions.size() - 1) {
        ChildWeeklySessions cwSessions = produceNewWeeklySessions();
        listOfWeeklySessions.push_back(cwSessions);
    }
    else {

    }
    currentIndex += 1;
    loadFromCWSessions(listOfWeeklySessions, currentIndex);
    updatePageLabel();
}


void SessionsForm::onPrevSessionsClicked() {
    if (currentIndex != 0) {
        bool isUpdated = updateWithWarningDialog();
        if (! isUpdated) return;

        currentIndex -= 1;
        loadFromCWSessions(listOfWeeklySessions, currentIndex);
        updatePageLabel();
    }

}


void SessionsForm::doInitialLoadFromMap(sessionsMap sessions) {

    if (sessions.size()==0) return;
    if ( sessions.find(child.id) == sessions.end() ) return;

    auto validSessions = SessionsHelpers::filterOldSessionsPerChild(sessions[child.id], 31);
    listOfWeeklySessions = validSessions;
    if (listOfWeeklySessions.size() == 0) {
        ChildWeeklySessions cwSessions = produceNewWeeklySessions();
        listOfWeeklySessions.push_back(cwSessions);
    }

    loadFromCWSessions(listOfWeeklySessions, 0);

}


ChildWeeklySessions SessionsForm::produceNewWeeklySessions() {
    ChildWeeklySessions cwSessions;
    cwSessions.childId = child.id;

    auto startDate = TimeUtils::getLaterTimeFromNow(7);
    startDate = TimeUtils::nextDayAfterTime(startDate, 1); // get first monday after
    auto endDate = TimeUtils::getLaterTimeFromNow(365*3);
    endDate = TimeUtils::nextDayAfterTime(endDate, 1); // get first monday after

    cwSessions.startDate = startDate;
    cwSessions.endDate = endDate;

    return cwSessions;
}



void SessionsForm::loadFromCWSessions(std::vector<ChildWeeklySessions> cwSessions, int index) {

    ChildWeeklySessions currentSessions = listOfWeeklySessions[index];

    std::vector<std::string> weeklyS = currentSessions.sessionsList;

    bool isMonAm = std::find(weeklyS.begin(), weeklyS.end(), "monAM") != weeklyS.end();
    bool isMonPm = std::find(weeklyS.begin(), weeklyS.end(), "monPM") != weeklyS.end();
    bool isTueAm = std::find(weeklyS.begin(), weeklyS.end(), "tueAM") != weeklyS.end();
    bool isTuePm = std::find(weeklyS.begin(), weeklyS.end(), "tuePM") != weeklyS.end();
    bool isWedAm = std::find(weeklyS.begin(), weeklyS.end(), "wedAM") != weeklyS.end();
    bool isWedPm = std::find(weeklyS.begin(), weeklyS.end(), "wedPM") != weeklyS.end();
    bool isThuAm = std::find(weeklyS.begin(), weeklyS.end(), "thuAM") != weeklyS.end();
    bool isThuPm = std::find(weeklyS.begin(), weeklyS.end(), "thuPM") != weeklyS.end();
    bool isFriAm = std::find(weeklyS.begin(), weeklyS.end(), "friAM") != weeklyS.end();
    bool isFriPm = std::find(weeklyS.begin(), weeklyS.end(), "friPM") != weeklyS.end();

    ui->monAMCheckBox->setChecked(isMonAm);
    ui->monPMCheckBox->setChecked(isMonPm);
    ui->tuesAMCheckBox->setChecked(isTueAm);
    ui->tuesPMCheckBox->setChecked(isTuePm);
    ui->wedAMCheckBox->setChecked(isWedAm);
    ui->wedPMCheckBox->setChecked(isWedPm);
    ui->thursAMCheckBox->setChecked(isThuAm);
    ui->thursPMCheckBox->setChecked(isThuPm);
    ui->fridayAMCheckBox->setChecked(isFriAm);
    ui->fridayPMCheckBox->setChecked(isFriPm);

    if (currentIndex < listOfWeeklySessions.size() - 1) {
        newSessionsButton->setText("Next");
    }
    else {
        newSessionsButton->setText("New");
    }

    if (currentIndex == 0) {
        prevSessionsButton->setEnabled(false);
    }
    else {
        prevSessionsButton->setEnabled(true);
    }

    QDate startDate = TimeUtils::timePointTQDate(currentSessions.startDate);
    QDate endDate = TimeUtils::timePointTQDate(currentSessions.endDate);
    startDateEdit->setDate(startDate);
    endDateEdit->setDate(endDate);

}


bool SessionsForm::updateWithWarningDialog() {
    try{
        updateListOfSessions();
        return true;
    }
    catch(InvalidSessionDates& e) {
        QMessageBox msgBox;
        msgBox.setText("Invalid dates - check end date is not before start date or doesn't overlap with existing");
        msgBox.exec();
        return false;
    }
}


void SessionsForm::updateListOfSessions() throw(InvalidSessionDates) {

    bool isMonAm = ui->monAMCheckBox->isChecked();
    bool isMonPm = ui->monPMCheckBox->isChecked();
    bool isTueAm = ui->tuesAMCheckBox->isChecked();
    bool isTuePm = ui->tuesPMCheckBox->isChecked();
    bool isWedAm = ui->wedAMCheckBox->isChecked();
    bool isWedPm = ui->monPMCheckBox->isChecked();
    bool isThuAm = ui->thursAMCheckBox->isChecked();
    bool isThuPm = ui->thursPMCheckBox->isChecked();
    bool isFriAm = ui->fridayAMCheckBox->isChecked();
    bool isFriPm = ui->fridayPMCheckBox->isChecked();

    ChildWeeklySessions sessions;
    sessions.childId = child.id;
    if (isMonAm) sessions.sessionsList.push_back("monAM");
    if (isMonPm) sessions.sessionsList.push_back("monPM");
    if (isTueAm) sessions.sessionsList.push_back("tueAM");
    if (isTuePm) sessions.sessionsList.push_back("tuePM");
    if (isWedAm) sessions.sessionsList.push_back("wedAM");
    if (isWedPm) sessions.sessionsList.push_back("wedPM");
    if (isThuAm) sessions.sessionsList.push_back("thuAM");
    if (isThuPm) sessions.sessionsList.push_back("thuPM");
    if (isFriAm) sessions.sessionsList.push_back("friAM");
    if (isFriPm) sessions.sessionsList.push_back("friPM");

    QDate startDate = startDateEdit->date();
    QDate endDate = endDateEdit->date();
    auto timePoint = TimeUtils::dateToTimePoint(startDate.day(), startDate.month(), startDate.year() );
    auto endTimePoint = TimeUtils::dateToTimePoint(endDate.day(), endDate.month(), endDate.year() );
    if (endTimePoint <= timePoint) throw InvalidSessionDates("Can't have end date before start date");

    sessions.startDate = timePoint;
    sessions.endDate = endTimePoint;

    bool isOverlap = avoidOverlap(sessions, listOfWeeklySessions);
    if (isOverlap == true) throw InvalidSessionDates("New dates overlap with existing");

    if (listOfWeeklySessions.size() == 0) listOfWeeklySessions.push_back(sessions);
    else listOfWeeklySessions[currentIndex] = sessions;
}


void SessionsForm::onSaveClicked() {

        bool isUpdated = updateWithWarningDialog();
        if (! isUpdated) return;
        sessionsM[child.id] = listOfWeeklySessions;

        SessionsReader sessionsReader;
        sessionsReader.writeSessions(sessionsM);
        navigator->goBack();
}


bool SessionsForm::avoidOverlap(ChildWeeklySessions newSessions,
                                std::vector<ChildWeeklySessions> existing) {
    bool overlap = false;

    for (int i = 0; i < existing.size(); i++) {
        bool localOverlap = false;
        auto existingS = existing[i];


        // if it starts before
        if ( (newSessions.startDate < existingS.startDate) &&
             (newSessions.endDate > existingS.startDate) ) {
            localOverlap = true;
        }
        // if it starts during
        if ( (newSessions.startDate >= existingS.startDate) &&
             (newSessions.startDate <= existingS.endDate) ) {
            localOverlap = true;
        }
        if (i == currentIndex) localOverlap = false;

        if (localOverlap) overlap = true;
    }
    return overlap;
}


SessionsForm::~SessionsForm()
{
    delete ui;
}
