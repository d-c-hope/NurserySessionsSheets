#include "newchildform.h"
#include "ui_newchildform.h"
#include <QPushButton>
#include <QString>
#include <iostream>
#include <chrono>
#include <ctime>
#include "child.h"
#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>

NewChildForm::NewChildForm(QWidget *parent, PageNavigator* _nav) :
    StackWidget(parent),
    ui(new Ui::NewChildForm)
{
    name = "new_child";
    ui->setupUi(this);
    navigator = _nav;
    std::vector<int> daysI;
    std::vector<int> monthsI;

    boost::push_back(daysI, boost::irange(1, 32));
    std::vector<std::string> days(daysI.size());
    std::transform (daysI.begin(), daysI.end(), days.begin(), [](int i) {
        return std::to_string(i);
    });

    std::vector<std::string> v = { "xyzzy", "plugh", "abracadabra" };
    std::vector<std::string> months = {"January", "February", "March", "April", "May", "June", "July","August","September","October","November","December"};

    std::vector<int> yearsI = getYears();

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

}


Child NewChildForm::getChild() {

    std::string firstName = ui->firstNameEdit->text().toStdString();
    std::string lastName = ui->lastNameEdit->text().toStdString();
    int day = ui->dayCombo->currentIndex();
    int month = ui->monthCombo->currentIndex();
    int yearIdx = ui->yearCombo->currentIndex();
    std::vector<int> years = getYears();
    int year = years[yearIdx];

    struct std::tm tm;
    memset(&tm, 0, sizeof(struct tm));
    tm.tm_year = year - 1900;
    tm.tm_mon = month;
    tm.tm_mday = day;
    auto ageTp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    Child c(firstName, lastName, ageTp);

    return c;

}


std::vector<int> NewChildForm::getYears() {
    // get the year now
    std::vector<int> yearsI;
    auto timeNow = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(timeNow);
    tm utc_tm = *gmtime(&tt);
    int yearNow = utc_tm.tm_year + 1900;

    boost::push_back(yearsI, boost::irange(yearNow-6, yearNow+1));

    return yearsI;
}


NewChildForm::~NewChildForm()
{
    delete ui;
}


void NewChildForm::onGoBackClicked() {
    std::cout << "Going back" << std::endl;
    navigator->goBack();
}










