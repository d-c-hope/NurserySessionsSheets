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

private:
    Ui::ChildListForm *ui;
    TableModel* model;
    PageNavigator* navigator;
    QPushButton* newChildButton;

public slots:
    void onRowDoubleClick(const QModelIndex&);
    void onNewChildClick();
};


#endif // CHILDLISTFORM_H
