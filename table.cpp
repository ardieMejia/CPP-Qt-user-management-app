#include "table.h"
#include <QDebug>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    mainHeader << "Column 1" << "Column 2" << "Column 3"; // Example headers
    
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return mainData.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return mainHeader.count();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        return mainData.at(index.row()).at(index.column());
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            // return mainHeader.at(section);
	  return m_horizontalHeaderData[section];
        } else {
            return section + 1; // Row numbers
        }
    }
    return QVariant();
}

void TableModel::addRow(const QStringList &rowData)
{
    beginInsertRows(QModelIndex(), mainData.count(), mainData.count());
    mainData.append(rowData);
    endInsertRows();
}

void TableModel::setData(int row, int column, const QVariant &value)
{
    if (row >= 0 && row < mainData.count() && column >= 0 && column < mainData.at(row).count()) {
        mainData[row][column] = value.toString();
        emit dataChanged(index(row, column), index(row, column), {Qt::DisplayRole});
    }
}

bool TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role)
{
  m_horizontalHeaderData[section] = value;
  headerDataChanged(orientation, section, section);  // emit signal!
  return true;
}


void TableModel::test_function(int index)
{
    // Delete button clicked

  qDebug() << "triggered successfully" << index;
}
