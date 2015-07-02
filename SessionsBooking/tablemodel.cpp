#include "tablemodel.h"
#include <iostream>
#include <sstream>
#include <iomanip>



TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}


TableModel::TableModel(std::vector<Child> _listOfChildren, QObject *parent)
    : QAbstractTableModel(parent)
{
    std::vector<Child> listofChildren2 = _listOfChildren;
    std::cout << _listOfChildren[0].firstName;
    listOfChildren = _listOfChildren;
    //std::cout << "raaa";
}


int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
//    std::cout << " In Row Count" << listOfChildren.size();
    return listOfChildren.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}


QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfChildren.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        Child child = listOfChildren[index.row()];
//        std::cout << "Getting item " << index.column() << std::endl;
        if (index.column() == 0)
               return QString::fromStdString(child.firstName);
        else if (index.column() == 1)
            return QString::fromStdString(child.lastName);
        else if (index.column() == 2) {
            std::stringstream s;
            std::time_t dobT = std::chrono::system_clock::to_time_t(child.dob);
            s << std::put_time(std::localtime(&dobT), "%d/%m/%Y");

            return QString::fromStdString(s.str());
        }
    }
    return QVariant();

}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("First Name");

            case 1:
                return tr("Last Name");

            case 2:
            return tr("Age");

            default:
                return QVariant();
        }
    }
    return QVariant();
}



std::vector<Child> TableModel::getListOfChildren() {
    return listOfChildren;
}


void TableModel::addItem(Child c) {
    QModelIndex mi;
    beginInsertRows(mi, listOfChildren.size(), listOfChildren.size());
    listOfChildren.push_back(c);
    endInsertRows();
//    emit editCompleted( true );
}


void TableModel::updateItem(Child orig, Child updated) {
    QModelIndex mi;
    beginInsertRows(mi, listOfChildren.size(), listOfChildren.size());
    auto it = find (listOfChildren.begin(), listOfChildren.end(), orig);
    *it = updated;
    endInsertRows();
}





