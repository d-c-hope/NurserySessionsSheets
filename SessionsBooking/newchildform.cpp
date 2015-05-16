#include "newchild.h"
#include "ui_newchild.h"

NewChild::NewChild(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewChild)
{
    ui->setupUi(this);
}

NewChild::~NewChild()
{
    delete ui;
}
