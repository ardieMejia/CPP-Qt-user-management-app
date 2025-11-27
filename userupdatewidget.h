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
  UserUpdateWidget(QWidget *parent = nullptr, int userId = -1, int userDepartmentId = -1);
  ~UserUpdateWidget();


private slots:
  void on_UserUpdateButton_clicked();
  void updateUser();


/* public slots: */

  


private:
  Ui::UserUpdateWidget *ui;
  QStringListModel *modelCombo1;
  QStandardItemModel *modelCombo2;
  QSqlQueryModel *modelDepartment;
  QSqlQueryModel *modelUser;
  int m_userId;
  int m_userDepartmentId;



};














#endif // USERUPDATEWIDGET_H
