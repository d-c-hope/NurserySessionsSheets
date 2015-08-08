#ifndef CHILDLISTFORM_H
#define CHILDLISTFORM_H

#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QPushButton>
#include <QtGlobal>
#include "child.h"
#include "tablemodel.h"
#include "pagenavigator.h"
#include "stackWidget.h"


namespace Ui {
class ChildListForm;
}

class ChildListForm : public StackWidget
{
    Q_OBJECT

public:
    QTableView* tView;
    explicit ChildListForm(QWidget *parent = 0, PageNavigator* _navigator = nullptr);
    ~ChildListForm();
    void addChild(Child child);
    void updateChild(Child original, Child child, bool isDeleted);
    Child selectedChild;

private:
    Ui::ChildListForm *ui;
    TableModel* model;
    PageNavigator* navigator;
    QPushButton* newChildButton;
    QPushButton* sessionsButton;
    QPushButton* printSessionsButton;

public slots:
    void onRowDoubleClick(const QModelIndex&);
    void onRowSingleClick(const QModelIndex&);
    void onNewChildClick();
    void onSessionsClick();
    void onPrintSessionsClick();
};


#endif // CHILDLISTFORM_H
