

#include <iostream>
#include "insertuserwindow.h"
#include "ui_insertuserwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>



  


InsertUserWindow::InsertUserWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::InsertUserWindow)
{
  ui->setupUi(this);



  
  // if (QMessageBox::Yes == QMessageBox::question(this, "Continue Database from scratch (removing all previous DB entries)?", "No!", QMessageBox::Yes | QMessageBox::No)){
  //   _restart_database();
  // }
    


  
}

InsertUserWindow::~InsertUserWindow()
{
  delete ui;
}











