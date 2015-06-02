#include "editchildform.h"
#include "ui_editchildform.h"

EditChildForm::EditChildForm(QWidget *parent, PageNavigator* _nav) :
    StackWidget(parent),
    ui(new Ui::EditChildForm)
{
    name = "edit_child";
    ui->setupUi(this);
    navigator = _nav;
}


EditChildForm::~EditChildForm()
{
    delete ui;
}
