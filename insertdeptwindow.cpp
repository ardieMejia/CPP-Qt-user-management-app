

#include <iostream>
#include "insertdeptwindow.h"
#include "ui_insertdeptwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include "database.h"


  


InsertDeptWindow::InsertDeptWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::InsertDeptWindow)
{
  ui->setupUi(this);


  
}

InsertDeptWindow::~InsertDeptWindow()
{
  delete ui;
}



void InsertDeptWindow::on_insertDept_clicked(){

  DBconnectionStatus resultString = _openDatabase();
  qDebug() << QString::fromStdString(resultString.statusString);
  QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
  QSqlQuery query(db);
  query.prepare("INSERT INTO departments (department_name) "
		"VALUES (:department_name)");
  // query.bindValue(":id", 1001);
  // qDebug() << "textstring get " <<;
  QString department_name = ui->textEditDeptName->toPlainText();

  query.bindValue(":department_name", department_name);
  bool result = query.exec();
  // if (result){
  //   isUsersTableFilled = true;
  // }
}









