#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStringListModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QVariant>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

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
  void on_buttonDeleteSelection_clicked();
  void on_buttonTableExists_clicked();
  void deleteUser(QVector<int> &arr);
  void viewGetUpdate(const QModelIndex &index);
  void on_insertUserDialog_clicked();
  void on_updateUser_clicked();

public slots:
  void test_function(int index);
  void test_text_edit();
  


private:
  Ui::MainWindow *ui;
  QLabel *myLabel;
  QStringListModel *modelHack;
  QStringListModel *model2;
  QSqlQueryModel *modelUser;
  QString textInput_model;
  // QAbstractItemModel *testmodel;

  QStandardItemModel *modelCurrentUser;
  // QAbstractItemModel modelTableUserAbstract;
  // QSqlRecord *recordUser const;




};



// ==================== attempt at using 2 parent classes into one



class myTestDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    myTestDelegate(QObject *parent = nullptr);
    ~myTestDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

// ==================== attempt at using 2 parent classes into one



#endif // MAINWINDOW_H
