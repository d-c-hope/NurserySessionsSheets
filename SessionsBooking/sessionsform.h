#ifndef SESSIONSFORM_H
#define SESSIONSFORM_H

#include <QWidget>

#include "pagenavigator.h"
#include "stackWidget.h"
#include "child.h"
#include <QPushButton>
#include <QDateEdit>
#include <QCheckBox>
#include <QLabel>
#include "childWeeklySessions.h"
#include "sessionsreader.h"



enum SessionsViewType{
    CURRENT, NEXT, NEW
};


namespace Ui {
class SessionsForm;
}

class InvalidSessionDates : public std::runtime_error {
public:
    InvalidSessionDates(const std::string& msg="") : runtime_error(msg) {}
};

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
    QPushButton* newSessionsButton;
    QPushButton* prevSessionsButton;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QDateEdit* startDateEdit;
    QDateEdit* endDateEdit;
    QLabel* titleTextLabel;
    QLabel* subTitleTextLabel;

    SessionsViewType viewType;

    std::vector<ChildWeeklySessions> listOfWeeklySessions;
    int currentIndex = 0;

    bool isOnCurrent;

    sessionsMap sessionsM;

    void updateListOfSessions() throw(InvalidSessionDates);
    bool updateWithWarningDialog();
    bool avoidOverlap(ChildWeeklySessions newSessions,
                                    std::vector<ChildWeeklySessions> existing);
    void doInitialLoadFromMap(sessionsMap sessions);
    void loadFromCWSessions(std::vector<ChildWeeklySessions> cwSessions, int index);
    ChildWeeklySessions produceNewWeeklySessions();
    void updatePageLabel();


public slots:
    void onSaveClicked();
    void onCancelClicked();
    void onNewSessionsClicked();
    void onPrevSessionsClicked();


};



#endif // SESSIONSFORM_H
