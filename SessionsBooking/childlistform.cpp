#include "QFileDialog"
#include "QString"
#include "QStringList"
#include "QStandardPaths"
#include <QStyle>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>


#include "childlistform.h"
#include "ui_childlistform.h"
#include "childlistreader.h"
#include "tablemodel.h"
#include "child.h"
#include "attendancesheets.h"
#include "timeutils.h"
#include "appConstants.h"
#include <sstream>



ChildListForm::ChildListForm(QWidget *parent, PageNavigator* _navigator) :
    StackWidget(parent),
    ui(new Ui::ChildListForm)
{
    ui->setupUi(this);
    newChildButton = ui->addChildButton;
    sessionsButton = ui->sessionsButton;
    printSessionsButton = ui->printSessionsButton;
    navigator = _navigator;
    ChildListReader clReader;
    std::vector<Child> children = clReader.readList();
    if (children.size() > 0) selectedChild = children[0];

    model = new TableModel(children, std::vector<std::string>{"First Name", "Last Name", "DOB"});

    tView = ui->tableView;
    tView->setSelectionBehavior(QAbstractItemView::SelectRows);
    model->setHeaderData(0, Qt::Horizontal, tr("Name"));


    tView->setModel(model);
    tView->setColumnWidth(0,180);
    tView->setColumnWidth(1,180);
    tView->setColumnWidth(2,100);

    int vwidth = tView->verticalHeader()->width();
    int hwidth = tView->horizontalHeader()->length();
    int swidth = 0;//tView->style()->pixelMetric(QStyle::PM_ScrollBarExtent);
    int fwidth = tView->frameWidth() * 2;

    tView->setFixedWidth(vwidth + hwidth + swidth + fwidth);

    std::vector<std::string> months = {"January", "February", "March", "April", "May", "June", "July","August","September","October","November","December"};
    std::vector<int> yearsI = TimeUtils::getYears(1,3);

    std::vector<std::string> years(yearsI.size());
    std::transform (yearsI.begin(), yearsI.end(), years.begin(), [](int i) {
        return std::to_string(i);
    });

    for (auto month: months) {
        ui->monthCombo->addItem(QString::fromStdString(month));
    }
    for (auto year: years) {
        ui->yearCombo->addItem(QString::fromStdString(year));
    }

    std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
    auto dateNow = TimeUtils::timePointToDate(timeNow);
    ui->monthCombo->setCurrentIndex(std::get<1>(dateNow) - 1);
    ui->yearCombo->setCurrentIndex(1);


    connect(tView, SIGNAL ( doubleClicked(const QModelIndex&)), this, SLOT ( onRowDoubleClick(const QModelIndex&)));
    connect(tView, SIGNAL ( clicked(const QModelIndex&)), this, SLOT ( onRowSingleClick(const QModelIndex&)));
    connect(newChildButton, SIGNAL ( clicked() ), this, SLOT ( onNewChildClick() ) );
    connect(sessionsButton, SIGNAL ( clicked() ), this, SLOT ( onSessionsClick() ) );
    connect(printSessionsButton, SIGNAL ( clicked() ), this, SLOT ( onPrintSessionsClick() ) );

}


ChildListForm::~ChildListForm()
{
    delete ui;
}


void ChildListForm::onRowDoubleClick(const QModelIndex& index) {
    auto listOfChildren = model->getListOfChildren();
    Child child = listOfChildren[index.row()];
    selectedChild = child;
    navigator->goToPage("edit_child");
}


void ChildListForm::onRowSingleClick(const QModelIndex& index) {
    auto listOfChildren = model->getListOfChildren();
    Child child = listOfChildren[index.row()];
    selectedChild = child;
}


void ChildListForm::onNewChildClick() {
    auto listOfChildren = model->getListOfChildren();
    navigator->goToPage("new_child");
}


void ChildListForm::onSessionsClick() {
    navigator->goToPage("sessions");
}


void ChildListForm::onPrintSessionsClick() {

    int month = ui->monthCombo->currentIndex()+1;
    int yearIdx = ui->yearCombo->currentIndex();
    std::vector<int> years = TimeUtils::getYears(1, 3);
    int year = years[yearIdx];

    auto children = model->getListOfChildren();

    std::vector<std::string> sheets = AttendanceSheets::createSheets(children, MonthRange(month, month, year, year));
    std::string sheetText = sheets[0];

    std::ostringstream filepath(AppConstants::defaultMonthFilePrefix, std::ios_base::ate);
    filepath << TimeUtils::months[month-1] << "_" << year << ".csv";

    QString selFilename  = QFileDialog::getSaveFileName(this, tr("Save File"),
                               QString::fromStdString(filepath.str()));


    std::ofstream out(selFilename.toStdString());
    out << sheetText;

}


void ChildListForm::addChild(Child child) {
    model->addItem(child);
    ChildListReader clReader;
    clReader.writeList(model->getListOfChildren());
}


void ChildListForm::updateChild(Child original, Child updated, bool isDeleted) {
    if (! isDeleted) model->updateItem(original, updated);
    else model->removeItem(original);
    ChildListReader clReader;
    clReader.writeList(model->getListOfChildren());

}



















