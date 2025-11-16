#ifndef INSERTDEPTWINDOW_H
#define INSERTDEPTWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QStringListModel>



#include "specialbox.h"
#include "table.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InsertDeptWindow; }
QT_END_NAMESPACE

class InsertDeptWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  InsertDeptWindow(QWidget *parent = nullptr);
  ~InsertDeptWindow();
  void _restart_database();


private slots:
  void on_insertDept_clicked();

public slots:

  


private:
  Ui::InsertDeptWindow *ui;


};
#endif // INSERTDEPTWINDOW_H
