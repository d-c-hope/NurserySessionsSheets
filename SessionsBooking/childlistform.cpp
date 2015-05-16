#include "childlistform.h"
#include "ui_childlistform.h"

ChildListForm::ChildListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildListForm)
{
    ui->setupUi(this);
}

ChildListForm::~ChildListForm()
{
    delete ui;
}
