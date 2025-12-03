#include <iostream>
#include <vector>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "table.h"
#include "adminwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlField>
#include <QSqlError>
#include <QDebug>
#include <QTableView>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QVector>
#include "database.h"
#include <QMessageBox>
#include <QDir>
#include <QSpinBox>
// #include <QSqlRecord>
#include "insertuserwindow.h"
#include "insertdeptwindow.h"
#include "userupdatewidget.h"




  


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);


  
  g_current_connection_status = _openDatabase();
  ui->userTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  connect(ui->userTableView, &QTableView::doubleClicked, this, &MainWindow::viewGetUpdate);

  
  
}

MainWindow::~MainWindow()
{
  delete ui;
}





void MainWindow::call_me(){
  std::cout << "im calling from another function";
  
}
  
void MainWindow::on_pushButton_clicked(){
  AdminWindow *adminwindow = new AdminWindow(this);
  adminwindow->show();
}




// ===== better remove index argument
void MainWindow::viewGetUpdate(const QModelIndex &index){

  if (modelUser->rowCount()){
    QSqlRecord recordUser;
    recordUser = modelUser->record(index.row());
    bool ok;
    int userId = modelUser->record(index.row()).field("id").value().toInt(&ok);
    int userDepartmentId = modelUser->record(index.row()).field(3).value().toInt(&ok);
    // ===== apparently the name is useless when gotten through:
    // ===== modelUser->record(index.row()).fieldName(3);
    UserUpdateWidget *userupdatewidget = new UserUpdateWidget(this, userId, userDepartmentId);
    
    userupdatewidget->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    userupdatewidget->show();
    
  }


}








void MainWindow::on_buttonGetAllUsers_clicked (){

  if(modelUserTable){
    qDebug() << modelUserTable->rowCount();
      if(modelUserTable->rowCount()){
	qDebug() << "helo";
	ui->userTableView->setModel(modelUserTable);
	// ui->userTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
	ui->userTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	// ui->userTableView->doubleClicked.connect(viewGetUpdate);
	
	ui->userTableView->show();
      }
    }

}


void MainWindow::on_buttonGetAllDept_clicked (){

  if(modelDepartmentTable){
    qDebug() << modelDepartmentTable->rowCount();
      if(modelDepartmentTable->rowCount()){
	qDebug() << "helo";
	ui->departmentTableView->setModel(modelDepartmentTable);
	ui->departmentTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	
	ui->departmentTableView->show();
      }
    }

}
		  
void MainWindow::deleteUser(int userId){
  		  
  qDebug() << "we deleted user";

  
  // QVariant resultString = _openDatabase();
  QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
  QSqlQuery query(db);
  


  // for(int &id : arr){
  //   qDebug() << "asd";
  //   // QVariant _variantList = QVariant::fromValue(arr);
  //   query.prepare("DELETE FROM users "
  // 		  "WHERE id = :id");
  //   query.bindValue(":id", id);
  //   bool result = query.exec();
  //   qDebug() << "current result : " << result;
  //   QSqlError error = query.lastError();
  //   qDebug() << error;
  // }

  


  query.prepare("DELETE FROM users "
		"WHERE id = :id");
  query.bindValue(":id", userId);
  bool result = query.exec();
  qDebug() << "current result : " << result;
  QSqlError error = query.lastError();
  qDebug() << error;
  

}



void MainWindow::deleteDepartment(int departmentId){
  		  
  qDebug() << "we deleted user";

  
  // QVariant resultString = _openDatabase();
  QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
  QSqlQuery query(db);
  


  // for(int &id : arr){
  //   qDebug() << "asd";
  //   // QVariant _variantList = QVariant::fromValue(arr);
  //   query.prepare("DELETE FROM users "
  // 		  "WHERE id = :id");
  //   query.bindValue(":id", id);
  //   bool result = query.exec();
  //   qDebug() << "current result : " << result;
  //   QSqlError error = query.lastError();
  //   qDebug() << error;
  // }

  


  query.prepare("DELETE FROM departments "
		"WHERE id = :id");
  query.bindValue(":id", departmentId);
  bool result = query.exec();
  qDebug() << "current result : " << result;
  QSqlError error = query.lastError();
  qDebug() << error;
  

}


void MainWindow::on_buttonDeleteSelection_clicked (){


  if (QMessageBox::Yes == QMessageBox::question(this, "Delete selected entries?", "Continue?", QMessageBox::Yes | QMessageBox::No)){
    QItemSelectionModel* selectionModel = ui->userTableView->selectionModel();

    // ===== this seems like a powerful feature, can do something with the selection model, should explore this one
    if (selectionModel){
      QModelIndexList indexes = selectionModel->selectedIndexes();
      QModelIndex index = indexes.at(0);
      int userId = index.data().toInt();
      deleteUser(userId);
    }
  }
   
}


void MainWindow::on_buttonDeleteDeptSelection_clicked (){


  if (QMessageBox::Yes == QMessageBox::question(this, "Delete selected entries?", "Continue?", QMessageBox::Yes | QMessageBox::No)){
    QItemSelectionModel* selectionModel = ui->departmentTableView->selectionModel();

    // ===== this seems like a powerful feature, can do something with the selection model, should explore this one
    if (selectionModel){
      QModelIndexList indexes = selectionModel->selectedIndexes();
      QModelIndex index = indexes.at(0);
      int departmentId = index.data().toInt();
      deleteDepartment(departmentId);
    }
  }
   
}


void MainWindow::on_buttonTableExists_clicked (){

 // TODO: we should check if database and tables exist
  // DBconnectionStatus result = _openDatabase();
  // qDebug() << result;
  // qDebug() << result;
  // qDebug() << result;


  // DBconnectionStatus g_current_connection_status;

  qDebug() << QString::fromStdString(g_current_connection_status.statusString);

  if(g_current_connection_status.status){    
    // isUsersTableFilled = true;
    QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
    QSqlQuery query(db);
    

    query.prepare("SELECT users.id, users.name, users.age, departments.id, departments.department_name FROM users LEFT OUTER JOIN departments ON users.department_id = departments.id");
    query.exec();
    
    
    modelUser = new QSqlQueryModel();
    modelUser->setQuery(query);


    qDebug() << "testing";
    int countModelUserRows = modelUser->rowCount();
    int countModelUserColumns = modelUser->columnCount() - 1;



    // ==================================================    
    modelUserTable = new QStandardItemModel(countModelUserRows, countModelUserColumns);    
    modelUserTable->setHeaderData(0, Qt::Horizontal, "ID");
    modelUserTable->setHeaderData(1, Qt::Horizontal, "Name");
    modelUserTable->setHeaderData(2, Qt::Horizontal, "Age");
    modelUserTable->setHeaderData(3, Qt::Horizontal, "Department Name");
    
    
    for(int row = 0; row < countModelUserRows; row++){
	QList<QStandardItem *> list;
	modelUserTable->setItem(row, 0, new QStandardItem(modelUser->record(row).field(0).value().toString()));//id
	modelUserTable->setItem(row, 1, new QStandardItem(modelUser->record(row).field(1).value().toString()));//name
	modelUserTable->setItem(row, 2, new QStandardItem(modelUser->record(row).field(2).value().toString()));//age
	modelUserTable->setItem(row, 3, new QStandardItem(modelUser->record(row).field(4).value().toString()));//department name
    }


    
    // ==================================================    
    
  

  }

  
}
void MainWindow::on_buttonDeptTableExists_clicked (){

 // TODO: we should check if database and tables exist
  // DBconnectionStatus result = _openDatabase();
  // qDebug() << result;
  // qDebug() << result;
  // qDebug() << result;


  // DBconnectionStatus g_current_connection_status;

  qDebug() << QString::fromStdString(g_current_connection_status.statusString);

  if(g_current_connection_status.status){    
    // isUsersTableFilled = true;
    QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
    QSqlQuery query(db);
    

    query.prepare("SELECT * FROM departments");
    query.exec();
    
    
    modelDepartment = new QSqlQueryModel();
    modelDepartment->setQuery(query);


    qDebug() << "testing";
    int countModelDepartmentRows = modelDepartment->rowCount();
    int countModelDepartmentColumns = modelDepartment->columnCount() - 1;


    // ==================================================    
    modelDepartmentTable = new QStandardItemModel(countModelDepartmentRows, countModelDepartmentColumns);
    modelDepartmentTable->setHeaderData(0, Qt::Horizontal, "ID");
    modelDepartmentTable->setHeaderData(3, Qt::Horizontal, "Department Name");
    
    
    for(int row = 0; row < countModelDepartmentRows; row++){
	QList<QStandardItem *> list;
	modelDepartmentTable->setItem(row, 0, new QStandardItem(modelDepartment->record(row).field(0).value().toString()));//id
	modelDepartmentTable->setItem(row, 1, new QStandardItem(modelDepartment->record(row).field(1).value().toString()));//name
    }


    
    // ==================================================    
    
  

  }

  
}
















void MainWindow::on_insertUserDialog_clicked(){
  InsertUserWindow *insertuserwindow = new InsertUserWindow(this);
  insertuserwindow->show();
}


void MainWindow::on_insertDepartmentDialog_clicked(){
  InsertDeptWindow *insertdeptwindow = new InsertDeptWindow(this);
  insertdeptwindow->show();
}


