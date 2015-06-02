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
    navigator = _navigator;
    ChildListReader clReader;
    std::vector<Child> children = clReader.readList("");

    model = new TableModel(children);

    tView = ui->tableView;
    tView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tView->setModel(model);

    connect(tView, SIGNAL ( doubleClicked(const QModelIndex&)), this, SLOT ( onRowDoubleClick(const QModelIndex&)));
    connect(newChildButton, SIGNAL ( clicked() ), this, SLOT ( onNewChildClick() ) );

}

ChildListForm::~ChildListForm()
{
    delete ui;
}


void ChildListForm::onRowDoubleClick(const QModelIndex& index) {
    auto listOfChildren = model->getListOfChildren();
    Child child = listOfChildren[index.row()];
    std::cout << "On double click on " << child.firstName << child.lastName  << std::endl;
    navigator->goToPage("new_child");
}


void ChildListForm::onNewChildClick() {
    auto listOfChildren = model->getListOfChildren();
//    Child child = listOfChildren[index.row()];
//    std::cout << "On double click on " << child.firstName << child.lastName  << std::endl;
    navigator->goToPage("new_child");
}



TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}


TableModel::TableModel(std::vector<Child> _listOfChildren, QObject *parent)
    : QAbstractTableModel(parent)
{
    std::vector<Child> listofChildren2 = _listOfChildren;
    std::cout << _listOfChildren[0].firstName;
    listOfChildren = _listOfChildren;
    //std::cout << "raaa";
}




