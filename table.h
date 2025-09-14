#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QStringList>
#include <QHash>

class TableModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  /* define initializer */
  explicit TableModel(QObject *parent = nullptr);

  // Basic model functions
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  // Functions to add/modify data
  void addRow(const QStringList &rowData);
  void setData(int row, int column, const QVariant &value);
  bool setHeaderData (int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::DisplayRole);

public slots:
  void test_function(int index);
  
private:
  QList<QStringList> mainData;
  QStringList mainHeader;
  QHash<int, QVariant> m_horizontalHeaderData;
};

#endif // MODEL_H
