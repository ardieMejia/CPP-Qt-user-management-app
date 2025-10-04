

#include <iostream>
#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include "database.h"
#include <QVariant>

  


AdminWindow::AdminWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::AdminWindow)
{
  ui->setupUi(this);


  // ===== Activity label
  ui->label->setAlignment(Qt::AlignTop);
  ui->label->setText("This label shows status (success/error) of recent activity ");
  // ===== Activity label
  
  // if (QMessageBox::Yes == QMessageBox::question(this, "Continue Database from scratch (removing all previous DB entries)?", "No!", QMessageBox::Yes | QMessageBox::No)){
  //   _restart_database();
  // }


  menubar = new QMenuBar(this);
  fileMenu = menubar->addMenu(tr("&Database"));
  // fileMenu = new QMenu();
  QAction *actionDnR = new QAction("Drop and Recreate", this);
  fileMenu->addAction(actionDnR); 
  // menubar->addMenu(fileMenu);

  connect(actionDnR, &QAction::triggered, this, &AdminWindow::_restart_database);
  // connect(ui->textEdit_ssync, &QTextEdit::textChanged, this, &MainWindow::test_text_edit);




  
}

AdminWindow::~AdminWindow()
{
  delete ui;
}



void AdminWindow::_restart_database()
{

  ui->textEdit->append("Text inserted by button.\n"); // Appends text to a new line




  QVariant resultString = _openDatabase();
  
  
  

  QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
  
  // std::cout << db;
  QSqlQuery query(db);

  QString queryDropAll = "DROP SCHEMA public CASCADE";
  QString queryRecreateAll = "CREATE SCHEMA public";
  QString queryGrantPost = "GRANT ALL ON SCHEMA public TO postgres;";
  QString queryGrantPublic = "GRANT ALL ON SCHEMA public TO public;";


  if (query.exec(queryDropAll)){
    qDebug() << "Table dropped successfully!!" ;
  }else{
    qDebug() << "Something went wrong" << query.lastError().text();
  }
  
  if (query.exec(queryRecreateAll)){
    qDebug() << "Table  created successfully!!" ;
  }else{
    qDebug() << "Something went wrong" << query.lastError().text();
  }
  
  if (query.exec(queryGrantPost)){
    qDebug() << "Table granted to postgresql successfully!!" ;
  }else{
    qDebug() << "Something went wrong" << query.lastError().text();
  }
  
  if (query.exec(queryGrantPublic)){
    qDebug() << "Table  granted to public successfully!!" ;
  }else{
    qDebug() << "Something went wrong" << query.lastError().text();
  }
  

  QString queryCreateUsers = "CREATE TABLE IF NOT EXISTS users ("
    "id INT GENERATED ALWAYS AS IDENTITY,"
    "name VARCHAR (50) NOT NULL,"
    "age INT"
    ");";
  
  if (query.exec(queryCreateUsers)){
    qDebug() << "Table created successfully!!" ;
      }else{
    qDebug() << "Something went wrong" << query.lastError().text();
  }
  

  db.close();  
  
  // _closeDatabase();


}




















  



  





