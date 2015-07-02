#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QtGlobal>
#include "child.h"


class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = 0);
    TableModel(std::vector<Child> _listOfChildren, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    std::vector<Child> getListOfChildren();
    void addItem(Child c);
    void updateItem(Child original, Child updated);


private:
    std::vector<Child> listOfChildren;
};




#endif // TABLEMODEL_H



//    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
//    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;
//    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;
//    QList<QPair<QString, QString> > getList();
