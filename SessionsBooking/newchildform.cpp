#include "newchildform.h"
#include "ui_newchildform.h"
#include <QPushButton>
#include <QString>
#include <iostream>
#include <chrono>
#include <ctime>
#include "child.h"
#include "childlistreader.h"
#include "timeutils.h"
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

    std::vector<std::string> months = {"January", "February", "March", "April", "May", "June", "July","August","September","October","November","December"};

    std::vector<int> yearsI = TimeUtils::getYears(6, 0);

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
    QPushButton* cancelButton = ui->cancelButton;
    connect(goBackButton, SIGNAL ( clicked() ), this, SLOT ( onGoBackClicked()));
    connect(cancelButton, SIGNAL ( clicked() ), this, SLOT ( onCancelClicked()));

    isCancelled = false;
}


Child NewChildForm::getChild() {

    std::string firstName = ui->firstNameEdit->text().toStdString();
    std::string lastName = ui->lastNameEdit->text().toStdString();
    int day = ui->dayCombo->currentIndex()+1;
    int month = ui->monthCombo->currentIndex();
    int yearIdx = ui->yearCombo->currentIndex();
    std::vector<int> years = TimeUtils::getYears(6, 1);
    int year = years[yearIdx];

    struct std::tm tm;
    memset(&tm, 0, sizeof(struct tm));
    tm.tm_year = year - 1900;
    tm.tm_mon = month;
    tm.tm_mday = day;
    auto ageTp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    ChildListReader clReader;
    std::vector<Child> children = clReader.readList();
    int max = 0;
    if (children.size() > 0) {
        std::vector<int> childrenIds(children.size());

        std::transform(children.begin(), children.end(), childrenIds.begin(),
           [](Child child) -> double { return child.id; });
        auto it = max_element(std::begin(childrenIds), std::end(childrenIds));
        max = *it;
    }

    Child c(max+1, firstName, lastName, ageTp);

    return c;

}


NewChildForm::~NewChildForm()
{
    delete ui;
}


void NewChildForm::onGoBackClicked() {
    navigator->goBack();
}


void NewChildForm::onCancelClicked() {
    isCancelled = true;
    navigator->goBack();
}










