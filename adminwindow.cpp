

#include <iostream>
#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
// #include "insertuserwindow.h"


  


AdminWindow::AdminWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::AdminWindow)
{
  ui->setupUi(this);


  // ===== Activity label
  ui->label->setAlignment(Qt::AlignTop);
  ui->label->setText("This label shows status (success/error) of recent activity ");
  // ===== Activity label
  
  if (QMessageBox::Yes == QMessageBox::question(this, "Continue Database from scratch (removing all previous DB entries)?", "No!", QMessageBox::Yes | QMessageBox::No)){
    _restart_database();
  }
    


  
}

AdminWindow::~AdminWindow()
{
  delete ui;
}



void AdminWindow::_restart_database()
{
  // Accessing a QLabel named 'myLabel'
  ui->textEdit->append("Text inserted by button.\n"); // Appends text to a new line



  // ui->label->setAlignment(Qt::AlignTop);
    
  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");


  db.setHostName("dpg-d37auere5dus739709qg-a.singapore-postgres.render.com");
  db.setPort(5432); // Default PostgreSQL port
  db.setDatabaseName("vanilla_postgresql_1");
  db.setUserName("vanilla_postgresql_1_user");
  db.setPassword("2hiE2Y8h6GQr9vpnvcd71PS1WBDWsEi4");

  // qDebug() << "attempting to connect";

  if (!db.open()) {
    // qDebug() << "Error: Failed to connect to database:" << db.lastError().text();
    return;
  } else {

    ui->label->setText("Connected to database!");
  }

  
  QSqlQuery query(db);

  QString queryDropAll = "DROP SCHEMA public CASCADE";
  QString queryRecreateAll = "CREATE SCHEMA public";
  QString queryGrantPost = "GRANT ALL ON SCHEMA public TO postgres;";
  QString queryGrantPublic = "GRANT ALL ON SCHEMA public TO public;";


  if (query.exec(queryDropAll)){
    // qDebug() << "Table dropped successfully!!" ;
  }else{
    // qDebug() << "Something went wrong" << query.lastError().text();
  }
  
  if (query.exec(queryRecreateAll)){
    // qDebug() << "Table  successfully!!" ;
  }else{
    // qDebug() << "Something went wrong" << query.lastError().text();
  }
  
  if (query.exec(queryGrantPost)){
    // qDebug() << "Table  successfully!!" ;
  }else{
    // qDebug() << "Something went wrong" << query.lastError().text();
  }
  
  if (query.exec(queryGrantPublic)){
    // qDebug() << "Table  successfully!!" ;
  }else{
    // qDebug() << "Something went wrong" << query.lastError().text();
  }
  

  QString queryCreateUsers = "CREATE TABLE IF NOT EXISTS users ("
    "id INT GENERATED ALWAYS AS IDENTITY,"
    "name VARCHAR (50) NOT NULL,"
    "age INT"
    ");";
  
  if (query.exec(queryCreateUsers)){
    // qDebug() << "Table created successfully!!" ;
      }else{
    // qDebug() << "Something went wrong" << query.lastError().text();
  }
  

  
  
  db.close(); 


}






// void AdminWindow::on_insertUserDialog_clicked(){
//   InsertUserWindow *insertuserwindow = new InsertUserWindow();
// }













  



  





