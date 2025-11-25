#ifndef USERUPDATEWIDGET_H
#define USERUPDATEWIDGET_H

#include <QWidget>
#include <QStringListModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QStandardItemModel>

// #include <QDebug>



QT_BEGIN_NAMESPACE
namespace Ui { class UserUpdateWidget; }
QT_END_NAMESPACE




class UserUpdateWidget : public QWidget
{
  Q_OBJECT
  
public:
  UserUpdateWidget(QWidget *parent = nullptr, int indexDepartment = -1);
  ~UserUpdateWidget();


/* private slots: */


/* public slots: */

  


private:
  Ui::UserUpdateWidget *ui;
  QStringListModel *modelCombo1;
  QStandardItemModel *modelCombo2;
  QSqlQueryModel *modelDepartment;
  QSqlQueryModel *modelUser;
  int m_indexDepartment;



};














#endif // USERUPDATEWIDGET_H
