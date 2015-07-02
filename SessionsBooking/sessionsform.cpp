#include "sessionsform.h"
#include "ui_sessionsform.h"
#include "sessionsreader.h"
#include "timeutils.h"




SessionsForm::SessionsForm(Child child, QWidget *parent, PageNavigator* _navigator) :
    StackWidget(parent),
    ui(new Ui::SessionsForm)
{
    ui->setupUi(this);
    navigator = _navigator;

    this->child = child;

    saveButton = ui->saveButton;
    dateEdit = ui->dateEdit;
    connect(saveButton, SIGNAL ( clicked() ), this, SLOT ( onSaveClicked() ) );

    dateEdit->setDate(QDate::currentDate());

    SessionsReader sessionsReader;
    sessionsM = sessionsReader.readSessions("");
    loadFromExisting(sessionsM);
}


void SessionsForm::onSaveClicked() {
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

    Sessions sessions;
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

    QDate date = dateEdit->date();
    auto timePoint = TimeUtils::qdateToTimePoint(date.day(), date.month(), date.year() );
    sessions.startDate = timePoint;

    if ( sessionsM.find(sessions.childId) != sessionsM.end() ) {
        sessionsM[sessions.childId].push_back(sessions);
    } else {
        sessionsM[sessions.childId] = std::vector<Sessions>{sessions};
    }
    SessionsReader sessionsReader;
    sessionsReader.writeSessions(sessionsM, "");
    navigator->goBack();

}


void SessionsForm::loadFromExisting(sessionsMap sessions) {

    if (sessions.size()==0) return;
    if ( sessions.find(child.id) == sessions.end() ) return;

//    std::vector<Sessions> childList

    Sessions ses = sessions[child.id][0];
    std::vector<std::string> weeklyS = ses.sessionsList;

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
    ui->monAMCheckBox->setChecked(isMonPm);
    ui->tuesAMCheckBox->setChecked(isTueAm);
    ui->tuesPMCheckBox->setChecked(isTuePm);
    ui->wedAMCheckBox->setChecked(isWedAm);
    ui->wedPMCheckBox->setChecked(isWedPm);
    ui->thursAMCheckBox->setChecked(isThuAm);
    ui->thursPMCheckBox->setChecked(isThuPm);
    ui->fridayAMCheckBox->setChecked(isFriAm);
    ui->fridayPMCheckBox->setChecked(isFriPm);

//    	QDate(int y, int m, int d)
}


//void SessionsForm::onGoBackClicked() {
//    navigator->goBack();
//}


SessionsForm::~SessionsForm()
{
    delete ui;
}
