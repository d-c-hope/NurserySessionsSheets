#include "childlistform.h"
#include "ui_childlistform.h"
#include "childlistreader.h"
#include "tablemodel.h"
#include "child.h"


ChildListForm::ChildListForm(QWidget *parent, PageNavigator* _navigator) :
    StackWidget(parent),
    ui(new Ui::ChildListForm)
{
    ui->setupUi(this);
    newChildButton = ui->addChildButton;
    sessionsButton = ui->sessionsButton;
    navigator = _navigator;
    ChildListReader clReader;
    std::vector<Child> children = clReader.readList("");

    model = new TableModel(children);

    tView = ui->tableView;
    tView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tView->setModel(model);

    connect(tView, SIGNAL ( doubleClicked(const QModelIndex&)), this, SLOT ( onRowDoubleClick(const QModelIndex&)));
    connect(tView, SIGNAL ( clicked(const QModelIndex&)), this, SLOT ( onRowSingleClick(const QModelIndex&)));
    connect(newChildButton, SIGNAL ( clicked() ), this, SLOT ( onNewChildClick() ) );
    connect(sessionsButton, SIGNAL ( clicked() ), this, SLOT ( onSessionsClick() ) );

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


void ChildListForm::addChild(Child child) {
    model->addItem(child);
    ChildListReader clReader;
    clReader.writeList(model->getListOfChildren(), "");
}


void ChildListForm::updateChild(Child original, Child updated) {
    model->updateItem(original, updated);
    ChildListReader clReader;
    clReader.writeList(model->getListOfChildren(), "");
}



















