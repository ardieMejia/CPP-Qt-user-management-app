#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStringListModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QVariant>
#include <QStandardItemModel>
#include <QAbstractTableModel>

// #include <QDebug>

#include "specialbox.h"
#include "table.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void call_me();
  QString toPlainText();

private slots:
  // void on_pushButton_2_clicked();
  // void on_pushButton_3_clicked();
  // void on_pushButton_4_clicked();
  void on_pushButton_clicked();
  void on_buttonGetAllUsers_clicked();
  void on_buttonGetAllDept_clicked();
  void on_buttonDeleteSelection_clicked();
  void on_buttonDeleteDeptSelection_clicked();
  void on_buttonTableExists_clicked();
  void on_buttonDeptTableExists_clicked();
  void deleteUser(int userId);
  void deleteDepartment(int departmentId);
  void viewGetUpdate(const QModelIndex &index);
  void on_insertUserDialog_clicked();
  void on_insertDepartmentDialog_clicked();




  
private:
  Ui::MainWindow *ui;
  QLabel *myLabel;
  QStringListModel *modelHack;
  QStringListModel *model2;
  QSqlQueryModel *modelUser;
  QSqlQueryModel *modelDepartment;
  QString textInput_model;
  QStandardItemModel *modelUserTable;
  QStandardItemModel *modelDepartmentTable;
  // QAbstractItemModel *testmodel;

  QStandardItemModel *modelCurrentUser;
  // QAbstractItemModel modelTableUserAbstract;
  // QSqlRecord *recordUser const;




};












#endif // MAINWINDOW_H
