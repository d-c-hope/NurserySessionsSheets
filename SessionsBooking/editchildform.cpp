#include "editchildform.h"
#include "ui_editchildform.h"
#include <QPushButton>
#include <QString>
#include <iostream>
#include <chrono>
#include <ctime>
#include "child.h"
#include "timeutils.h"
#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <sstream>
#include <iomanip>



EditChildForm::EditChildForm(Child child, QWidget *parent, PageNavigator* _nav) :
    StackWidget(parent),
    ui(new Ui::EditChildForm)
{
    name = "edit_child";
    ui->setupUi(this);
    navigator = _nav;

    this->child = child;
    this->original = child;

    std::vector<int> daysI;
    std::vector<int> monthsI;

    boost::push_back(daysI, boost::irange(1, 32));
    std::vector<std::string> days(daysI.size());
    std::transform (daysI.begin(), daysI.end(), days.begin(), [](int i) {
        return std::to_string(i);
    });
    std::vector<std::string> months = {"January", "February", "March", "April", "May", "June", "July","August","September","October","November","December"};
    std::vector<int> yearsI = TimeUtils::getYears(6,1);

    std::vector<std::string> years(yearsI.size());
    std::transform (yearsI.begin(), yearsI.end(), years.begin(), [](int i) {
        return std::to_string(i);
    });



    for (auto day: days) {
        ui->dayCombo->addItem(QString::fromStdString(day));
    }
    for (auto month: months) {
        ui->monthCombo->addItem(QString::fromStdString(month));
    }
    for (auto year: years) {
        ui->yearCombo->addItem(QString::fromStdString(year));
    }

    QPushButton* goBackButton = ui->goBackButton;
    connect(goBackButton, SIGNAL ( clicked() ), this, SLOT ( onGoBackClicked()));

    QPushButton* deleteButton = ui->deleteButton;
    connect(deleteButton, SIGNAL ( clicked() ), this, SLOT ( onDeleteClicked()));

    ui->firstNameEdit->setText(QString::fromStdString(child.firstName));
    ui->lastNameEdit->setText(QString::fromStdString(child.lastName));
    std::chrono::system_clock::time_point dob = child.dob;

    time_t dobTime = std::chrono::system_clock::to_time_t(child.dob);


    std::stringstream s;
    std::time_t dobT = std::chrono::system_clock::to_time_t(child.dob);
    s << std::put_time(std::localtime(&dobT), "%d/%m/%Y");

    std::tm* dobTm = localtime( &dobTime);
    dobTm->tm_year;
    dobTm->tm_mday;
    dobTm->tm_year;
    ui->dayCombo->setCurrentIndex(dobTm->tm_mday - 1);
    ui->monthCombo->setCurrentIndex(dobTm->tm_mon);
    std::string yearStr = std::to_string(dobTm->tm_year + 1900);
    int yearIdx = 0;
    for (yearIdx; yearIdx < years.size(); yearIdx++) {
        if (years[yearIdx] == yearStr ) break;
    }
    ui->yearCombo->setCurrentIndex(yearIdx);

    childIsDeleted = false;
}


EditChildForm::~EditChildForm()
{
    delete ui;
}




void EditChildForm::onGoBackClicked() {
    navigator->goBack();
}


void EditChildForm::onDeleteClicked() {
    childIsDeleted = true;
    navigator->goBack();
}


Child EditChildForm::getChild() {

    std::string firstName = ui->firstNameEdit->text().toStdString();
    std::string lastName = ui->lastNameEdit->text().toStdString();
    int day = ui->dayCombo->currentIndex();
    int month = ui->monthCombo->currentIndex();
    int yearIdx = ui->yearCombo->currentIndex();
    std::vector<int> years = TimeUtils::getYears(6, 0);
    int year = years[yearIdx];

    struct std::tm tm;
    memset(&tm, 0, sizeof(struct tm));
    tm.tm_year = year - 1900;
    tm.tm_mon = month;
    tm.tm_mday = day;
    auto ageTp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    Child c(original.id, firstName, lastName, ageTp);

    return c;

}



Child EditChildForm::getOriginal() {
    return original;
}






