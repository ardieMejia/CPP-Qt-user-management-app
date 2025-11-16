#ifndef INSERTUSERWINDOW_H
#define INSERTUSERWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStringListModel>



#include "specialbox.h"
#include "table.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InsertUserWindow; }
QT_END_NAMESPACE

class InsertUserWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  InsertUserWindow(QWidget *parent = nullptr);
  ~InsertUserWindow();
  void _restart_database();


private slots:
  void on_insertUser_clicked();

public slots:

  


private:
  Ui::InsertUserWindow *ui;


};
#endif // INSERTUSERWINDOW_H
