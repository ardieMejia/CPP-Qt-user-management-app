#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStringListModel>
#include <QMenuBar>
#include <QMenu>

#include "specialbox.h"
#include "table.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AdminWindow; }
QT_END_NAMESPACE

class AdminWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  AdminWindow(QWidget *parent = nullptr);
  ~AdminWindow();
  void _restart_database();
  /* QString toPlainText(); */

private slots:
  /* void on_pushButton_2_clicked(); */
  /* void on_pushButton_3_clicked(); */
  /* void on_pushButton_4_clicked(); */
  /* void on_pushButton_clicked(); // Slot for a button named 'myButton' */
  /* void on_button_saveUser_clicked(); */
public slots:
  /* void test_function(int index); */
  /* void test_text_edit(); */





private:
  Ui::AdminWindow *ui;
  QMenuBar *menubar;
  QMenu *fileMenu;
  /* QLabel *myLabel; */
  /* QStringListModel *a_model; */
  /* QStringListModel *model2; */
  /* QString textInput_model; */

};
#endif // MAINWINDOW_H
