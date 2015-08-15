#include "tablemodel.h"
#include <iostream>
#include <sstream>
#include <iomanip>



TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}


TableModel::TableModel(std::vector<Child> _listOfChildren,
                       std::vector<std::string> _headerStrings,
                       QObject *parent)
    : QAbstractTableModel(parent)
{
    std::vector<Child> listofChildren2 = _listOfChildren;
    listOfChildren = _listOfChildren;
    headerStrings = _headerStrings;
}


int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
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
        if (static_cast<int>(section) < headerStrings.size()) return QString::fromStdString(headerStrings[section]);
        else return QVariant();
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
//    beginInsertRows(mi, listOfChildren.size(), listOfChildren.size());
    auto it = find (listOfChildren.begin(), listOfChildren.end(), orig);
    *it = updated;
//    endInsertRows();
}


void TableModel::removeItem(Child orig) {
    QModelIndex mi;
    auto it = find (listOfChildren.begin(), listOfChildren.end(), orig);
    int index = std::distance(listOfChildren.begin(), it);
    beginRemoveRows(mi, index, index);
    listOfChildren.erase (it);
    endRemoveRows();
}


//QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
//            const
//{
//    if (!hasIndex(row, column, parent))
//        return QModelIndex();

//    TreeItem *parentItem;

//    if (!parent.isValid())
//        parentItem = rootItem;
//    else
//        parentItem = static_cast<TreeItem*>(parent.internalPointer());

//    TreeItem *childItem = parentItem->child(row);
//    if (childItem)
//        return createIndex(row, column, childItem);
//    else
//        return QModelIndex();
//}










