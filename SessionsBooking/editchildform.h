#ifndef EDITCHILDFORM_H
#define EDITCHILDFORM_H

#include <QWidget>

#include <stackWidget.h>
#include <pagenavigator.h>
#include "child.h"


namespace Ui {
class EditChildForm;
}

class EditChildForm : public StackWidget
{
    Q_OBJECT

public:
    explicit EditChildForm(Child child, QWidget *parent = 0 , PageNavigator* _nav=nullptr);
    ~EditChildForm();
    Child getChild();
    Child getOriginal();

public slots:
    void onGoBackClicked();


private:
    Child child;
    Child original;
    Ui::EditChildForm *ui;
    PageNavigator* navigator;
};

#endif // EDITCHILDFORM_H
