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




  


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // ========================================
  





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




  connect(ui->comboBox_ssync, QOverload<int>::of(&QComboBox::currentIndexChanged), this, QOverload<int>::of(&MainWindow::test_function));
  connect(ui->textEdit_ssync, &QTextEdit::textChanged, this, &MainWindow::test_text_edit);

  







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





// static void fill_a_text()
// {
  // ui->label->setText("New Text After Button Click"); // Change the label text
// }


myTestDelegate::myTestDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    qDebug() << "myTestDelegate created";
}

myTestDelegate::~myTestDelegate()
{
    qDebug() << "ClassA destroyed";
}


// ==================================================
// ==================================================

QWidget *myTestDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{

  
  QComboBox *editor = new QComboBox(parent);
  QString var1 = QString("asd");
  QStringList var2;
  var2 << "asd" << "asd";
  QString var3 =  var2.join(QString(","));
  for (QString &item : var2){
    editor->addItem(item);
  }

  
  
  
  return editor;
}


void myTestDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
  // int value = index.data(Qt::EditRole).toInt();
  
  // QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
  // spinBox->setValue(value);

  QComboBox *cb = qobject_cast<QComboBox *>(editor);

  cb->setCurrentIndex(0);
}

void myTestDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
				  const QModelIndex &index) const
{
  // QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
  // spinBox->interpretText();
  //   int value = spinBox->value();
    
  //   model->setData(index, value, Qt::EditRole);

  QComboBox *cb = qobject_cast<QComboBox *>(editor);

  model->setData(index, cb->currentText(), Qt::EditRole);
//   QString underscore = "__";
//   QString total ="";
//   total += underscore;
//   total += cb->currentText();
//   model->setData(index, total, Qt::DisplayRole);
}

// QWidget *ComboBoxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
// {
//     // Create the combobox and populate it
//     QComboBox *cb = new QComboBox(parent);
//     const int row = index.row();
//     cb->addItem(QString("one in row %1").arg(row));
//     cb->addItem(QString("two in row %1").arg(row));
//     cb->addItem(QString("three in row %1").arg(row));
//     return cb;
// }

// ==================================================
// ==================================================
  

void MainWindow::viewGetUpdate(const QModelIndex &index){
  qDebug() << "some tests";

  QStringList list_;

  qDebug() << index.row();

// ================================================== just a test

  const QAbstractItemModel *testmodel = index.model();
  qDebug() << "testmodel:" << testmodel;

  qDebug() << QDir::currentPath();
  
// ================================================== just a test

  

  
  
  if (modelUser->rowCount()){


    
    
    QSqlRecord recordUser;
    recordUser = modelUser->record(index.row());



    
    modelCurrentUser = new QStandardItemModel(1, recordUser.count());
    // QTableView *modelTableUser = new QTableView();


    for (int column = 0; column < 3; column++){
      modelCurrentUser->setHeaderData(column, Qt::Horizontal, recordUser.fieldName(column));
      QSqlField fieldSql = recordUser.field(column);
      QString stringField = fieldSql.value().toString();
      QStandardItem *item = new QStandardItem(stringField);
      modelCurrentUser->setItem(0,column,item);
    }
    
    ui->userUpdateView->setModel(modelCurrentUser);
    ui->userUpdateView->setEditTriggers(QAbstractItemView::DoubleClicked);     
      // setSelectionBehavior(QAbstractItemView::SelectRows);

    myTestDelegate* myEditor = new myTestDelegate(ui->userUpdateView);

    ui->userUpdateView->setItemDelegateForColumn(1, myEditor);
    
    // QSqlTableModel modelTableUser;
    // modelTableUser.setRecord(0,recordUser);





    

    
  }

  
}



void MainWindow::on_buttonGetAllUsers_clicked (){








    // int value = 23;

    // QVariant a_variant1(value);
    
    // ui->textEdit_name->setText(a_variant1.toString());







  if(modelUser){
      
      if(modelUser->rowCount()){
	qDebug() << "helo";
	ui->userTableView->setModel(modelUser);
	ui->userTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
	ui->userTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	// ui->userTableView->doubleClicked.connect(viewGetUpdate);

	ui->userTableView->show();

      
      }

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
  DBconnectionStatus result = _openDatabase();
  // qDebug() << result;
  // qDebug() << result;
  // qDebug() << result;

  if(result.status){    
    // isUsersTableFilled = true;
    QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
    QSqlQuery query(db);
    
    query.prepare("SELECT * FROM users");
    query.exec();
    
    modelUser = new QSqlQueryModel();
    modelUser->setQuery(query);
  }

  
}




<<<<<<< HEAD
void MainWindow::on_updateUser_clicked()
=======
void MainWindow::_on_updateUser_clicked()
>>>>>>> working
{

  bool var1 = false;
  QVector<QString> values;
  if (modelCurrentUser){
<<<<<<< HEAD
    // ==================================================
=======

>>>>>>> working


    
    qDebug() << modelCurrentUser;
    qDebug() << modelCurrentUser->item(0,0)->text();
    for(int i=0; i<modelCurrentUser->columnCount();i++){     
      
      QModelIndex index = modelCurrentUser->index(0, i);
      if(modelCurrentUser->data(index).isNull()){	
	values.append("None");
      }else{	
	values.append(modelCurrentUser->item(0,i)->text());	
      }
    }
      
      
    QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
    QSqlQuery queryUpdate(db);


    bool ok;
    int _id = modelCurrentUser->item(0,0)->text().toInt(&ok);
    if (!ok){
      qDebug() << "oops";
    }

    queryUpdate.prepare("UPDATE users SET name = :name, age = :age WHERE id = :id");
    queryUpdate.bindValue(":name", values.at(1));
    queryUpdate.bindValue(":age", values.at(2));
    queryUpdate.bindValue(":id", _id);



    bool result = queryUpdate.exec();
    if(result){
      qDebug() << "fine";
    }
    QSqlError error = queryUpdate.lastError();
    qDebug() << error;

    
<<<<<<< HEAD
    // ==================================================
=======

>>>>>>> working
  }


    

  qDebug() << "here we know";

<<<<<<< HEAD

=======
>>>>>>> working
  
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


