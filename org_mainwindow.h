#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStringListModel>
#include <QSqlQueryModel>
#include <QVariant>

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
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_clicked();
  void on_buttonRefresh_clicked();
  void on_buttonDeleteSelection_clicked();
  void on_buttonTableExists_clicked();
  void deleteUser(QVector<int> &arr);
  void some_function();
  void on_insertUserDialog_clicked();

public slots:
  void test_function(int index);
  void test_text_edit();
  


private:
  Ui::MainWindow *ui;
  QLabel *myLabel;
  QStringListModel *a_model;
  QStringListModel *model2;
  QSqlQueryModel *modelUser;
  QString textInput_model;


};
#endif // MAINWINDOW_H
