#ifndef NEWCHILDFORM_H
#define NEWCHILDFORM_H

#include <QWidget>
#include <pagenavigator.h>
#include <stackWidget.h>
#include "child.h"

namespace Ui {
class NewChildForm;
}

class NewChildForm : public StackWidget
{
    Q_OBJECT

public:
    bool isCancelled;
    explicit NewChildForm(QWidget *parent = 0, PageNavigator* _nav = nullptr);
    ~NewChildForm();

    Child getChild();


public slots:
    void onGoBackClicked();
    void onCancelClicked();

private:
    Ui::NewChildForm *ui;
    PageNavigator* navigator;
};

#endif // NEWCHILDFORM_H
