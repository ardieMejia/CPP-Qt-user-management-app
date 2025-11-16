

#include <iostream>
#include "insertuserwindow.h"
#include "ui_insertuserwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include "database.h"


  


InsertUserWindow::InsertUserWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::InsertUserWindow)
{
  ui->setupUi(this);


  
}

InsertUserWindow::~InsertUserWindow()
{
  delete ui;
}



void InsertUserWindow::on_insertUser_clicked(){

  DBconnectionStatus resultString = _openDatabase();
  qDebug() << QString::fromStdString(resultString.statusString);
  QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
  QSqlQuery query(db);
  query.prepare("INSERT INTO users (name, age) "
		"VALUES (:name, :age)");
  // query.bindValue(":id", 1001);
  // qDebug() << "textstring get " <<;
  QString name = ui->textEditName->toPlainText();
  QString age = ui->textEditAge->toPlainText();
  query.bindValue(":name", name);
  query.bindValue(":age", age);
  bool result = query.exec();
  // if (result){
  //   isUsersTableFilled = true;
  // }
}









