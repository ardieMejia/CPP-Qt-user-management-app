#include <iostream>
#include <vector>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "table.h"
#include "adminwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QTableView>
#include <QItemSelectionModel>
#include <QVector>
#include "database.h"
#include <QMessageBox>
#include "insertuserwindow.h"




  


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // ========================================
  
  a_model = new QStringListModel(this);
  QStringList a_list;
  a_list << "Abu Yusuf" << "James Berg" << "Petra Hani";

  a_model->setStringList(a_list);

  ui->listView->setModel(a_model);
  ui->comboBox->setModel(a_model);

  ui->listView->
    setEditTriggers(QAbstractItemView::AnyKeyPressed |
		    QAbstractItemView::DoubleClicked);
  

  // ========================================



  // ++++++++++++++++++++++++++++++++++++++++++++++++++
  
  model2 = new QStringListModel(this);
  QStringList list2;
  list2 << "Hanifa" << "Bev" << "Ardie";
  model2->setStringList(list2);

  ui->comboBox_ssync->setModel(model2); 

  ui->textEdit_ssync->setText(textInput_model);


  // model3 = new QStringListModel(this);
  // QStringList list3;
  // list3 << "Kabul" << "South London" << "Kuala Lumpur";
  // model3->setStringList(list3);



  // connect(ui->comboBox_ssync, &QComboBox::currentIndexChanged, this,  QOverload(&MainWindow::test_function));
  connect(ui->comboBox_ssync, QOverload<int>::of(&QComboBox::currentIndexChanged), this, QOverload<int>::of(&MainWindow::test_function));
  connect(ui->textEdit_ssync, &QTextEdit::textChanged, this, &MainWindow::test_text_edit);
  // connect(ui->comboBox_ssync, QOverload<int>::of(&QComboBox::currentIndexChanged), this, QOverload<int>::of(&MainWindow::test_function));
  







  connect(ui->userTableView, &QTableView::doubleClicked, this, &MainWindow::some_function);










  
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





// static void fill_a_text()
// {
  // ui->label->setText("New Text After Button Click"); // Change the label text
// }




void MainWindow::some_function(){
  qDebug() << "some tests";
}



void MainWindow::on_buttonRefresh_clicked (){
  if (isUsersTableFilled){
    QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
    QSqlQuery query(db);

    query.prepare("SELECT * FROM users");
    query.exec();

    modelUser = new QSqlQueryModel();
    modelUser->setQuery(query);

    ui->userTableView->setModel(modelUser);
    ui->userTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->userTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // ui->userTableView->doubleClicked.connect(some_function);

    ui->userTableView->show();

    
  }  
}

void MainWindow::deleteUser(QVector<int>& arr){
  
  qDebug() << "we deleted user";

  
  // QVariant resultString = _openDatabase();
  QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
  QSqlQuery query(db);
  


  for(int &id : arr){
    qDebug() << "asd";
    // QVariant _variantList = QVariant::fromValue(arr);
    query.prepare("DELETE FROM users "
		  "WHERE id = :id");
    query.bindValue(":id", id);
    bool result = query.exec();
    qDebug() << "current result : " << result;
    QSqlError error = query.lastError();
    qDebug() << error;
  }






}


void MainWindow::on_buttonDeleteSelection_clicked (){


  if (QMessageBox::Yes == QMessageBox::question(this, "Delete selected entries?", "Continue?", QMessageBox::Yes | QMessageBox::No)){
    QItemSelectionModel* selectionModel = ui->userTableView->selectionModel();


    
    
    if (selectionModel){
      QModelIndexList indexes = selectionModel->selectedIndexes();
      if (indexes.size()){
	QVector<int> arr;
	for(int i=0; i < indexes.size();i++){
	  // QModelIndex index = new QModelIndex();
	  QModelIndex index = indexes.at(i);
	  qDebug() << index.data().toInt();
	  qDebug() << "asd";
	  // qDebug() << index.row();
	  // qDebug() << index.column();
	  if (index.column() == 0){
	    qDebug() << "---";
	    qDebug() << index.data().toInt();
	    qDebug() << "---";
	    arr.append(index.data().toInt());
	  }
	}
	deleteUser(arr);
      }
    }


  }
    


    

    
    
    // for (int i = 0; i < indexes.size(); ++i) {
    //   QModelIndex index = indexes.at(i);

    //   qDebug() << index.row();
    // }
   
}
void MainWindow::on_buttonTableExists_clicked (){

 // TODO: we should check if database and tables exist
  QVariant result = _openDatabase();

  isUsersTableFilled = true;
  
}

void MainWindow::on_pushButton_2_clicked()
{
    // Insert button clicked
  qDebug() << "hello there";

  // we get row for stupid C++ awareness
  int row = a_model->rowCount();
  a_model->insertRows(row,1);
  QModelIndex index = a_model->index(row);

  ui->listView->setCurrentIndex(index);
  ui->listView->edit(index);
  
  
}


void MainWindow::on_pushButton_3_clicked()
{
  // the number is protected by the index object, quite a stupid idea
  int row = ui->listView->currentIndex().row();

  a_model->insertRows(row,1);

  QModelIndex index = a_model->index(row);

  ui->listView->setCurrentIndex(index);
  ui->listView->edit(index);
}


void MainWindow::on_pushButton_4_clicked()
{
    // Delete button clicked
  a_model->removeRows(ui->listView->currentIndex().row(),1);
}


void MainWindow::test_function(int index)
{
    // Delete button clicked

  qDebug() << "triggered successfully getting index ";
  // modelIndex = QModelIndex
  // qDebug() << model2->data(model2->index(index),Qt::DisplayRole);

  
  QString fullname = model2->data(model2->index(index),Qt::DisplayRole).toString();

  
  if (fullname == "Hanifa"){    
    qDebug() << "matches";
  }
  // if model2->data(model2->index(index),Qt::DisplayRole);
}



void MainWindow::test_text_edit()
{
    // Delete button clicked

  qDebug() << "triggered successfully getting index ";
  // ===== we dont need model here, but we're not sure if there's an advantage
  qDebug() << "textstring get " <<  ui->textEdit_ssync->toPlainText();
  QString textname = ui->textEdit_ssync->toPlainText();

  
  int index = ui->comboBox_ssync->currentIndex();
  QString comboname = model2->data(model2->index(index),Qt::DisplayRole).toString();

  if (comboname == textname){
    qDebug() << "ITS THE SAME";
  }

}


void MainWindow::on_insertUserDialog_clicked(){
  InsertUserWindow *insertuserwindow = new InsertUserWindow(this);
  insertuserwindow->show();
}


