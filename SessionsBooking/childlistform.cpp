#include "QFileDialog"
#include "QString"
#include "QStringList"
#include "QStandardPaths"


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
    std::vector<Child> children = clReader.readList("");
    if (children.size() > 0) selectedChild = children[0];

    model = new TableModel(children);

    tView = ui->tableView;
    tView->setSelectionBehavior(QAbstractItemView::SelectRows);

    tView->setModel(model);


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
    std::cout << "On double click on " << child.firstName << child.lastName  << std::endl;
    navigator->goToPage("edit_child");
}


void ChildListForm::onRowSingleClick(const QModelIndex& index) {
    auto listOfChildren = model->getListOfChildren();
    Child child = listOfChildren[index.row()];
    selectedChild = child;
    std::cout << "On single click on " << child.firstName << child.lastName  << std::endl;
}


void ChildListForm::onNewChildClick() {
    auto listOfChildren = model->getListOfChildren();
//    Child child = listOfChildren[index.row()];
//    std::cout << "On double click on " << child.firstName << child.lastName  << std::endl;
    navigator->goToPage("new_child");
}


void ChildListForm::onSessionsClick() {
//    auto listOfChildren = model->getListOfChildren();
//    Child child = listOfChildren[index.row()];
//    std::cout << "On double click on " << child.firstName << child.lastName  << std::endl;
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

    std::cout << sheetText;
    std::ostringstream filename(AppConstants::defaultMonthFilePrefix, std::ios_base::ate);
    filename << TimeUtils::months[month-1] << "_" << year << ".csv";
    std::cout << filename.str();

    QStandardPaths::HomeLocation;

    QString selFilename  = QFileDialog::getSaveFileName(this, tr("Save File"),
                               QString::fromStdString("/Users/david_hope2/" + filename.str()));


    std::ofstream out(selFilename.toStdString());
    out << sheetText;

}


void ChildListForm::addChild(Child child) {
    model->addItem(child);
    ChildListReader clReader;
    clReader.writeList(model->getListOfChildren(), "");
}


void ChildListForm::updateChild(Child original, Child updated, bool isDeleted) {
    model->updateItem(original, updated);
    ChildListReader clReader;
    clReader.writeList(model->getListOfChildren(), "");
}



















