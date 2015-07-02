#ifndef SESSIONSFORM_H
#define SESSIONSFORM_H

#include <QWidget>

#include "pagenavigator.h"
#include "stackWidget.h"
#include "child.h"
#include <QPushButton>
#include <QDateEdit>
#include "sessions.h"
#include "sessionsreader.h"


namespace Ui {
class SessionsForm;
}

class SessionsForm : public StackWidget
{
    Q_OBJECT

public:
    explicit SessionsForm(Child child, QWidget *parent = 0, PageNavigator* _navigator = nullptr);
    ~SessionsForm();

private:
    Ui::SessionsForm *ui;
    PageNavigator* navigator;
    Child child;
    QPushButton* addChangeButton;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QDateEdit* dateEdit;

    sessionsMap sessionsM;

    void loadFromExisting(sessionsMap sessions);

public slots:
    void onSaveClicked();
//    void onGoBackClicked() {


};

#endif // SESSIONSFORM_H
