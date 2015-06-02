#ifndef EDITCHILDFORM_H
#define EDITCHILDFORM_H

#include <QWidget>

#include <stackWidget.h>
#include <pagenavigator.h>


namespace Ui {
class EditChildForm;
}

class EditChildForm : public StackWidget
{
    Q_OBJECT

public:
    explicit EditChildForm(QWidget *parent = 0, PageNavigator* _nav=nullptr);
    ~EditChildForm();

private:
    Ui::EditChildForm *ui;
    PageNavigator* navigator;
};

#endif // EDITCHILDFORM_H
