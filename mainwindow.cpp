#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "table.h"
#include "adminwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>





  


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
  

  
  // ui->comboBox_ssync->setModel(a_model);
  
  // ++++++++++++++++++++++++++++++++++++++++++++++++++

  

  // ui->label->setText("helloooo");
  
  // myLabel = new QLabel("Click Me", this);
  // myLabel->setGeometry(100, 100, 150, 30); // x, y, width, height

  // ui->pushButton->setText("Admin Window");
  
  // QObject::connect(ui->pushButton, &QPushButton::clicked, [&]() {
  //   ui->textEdit->append("Text inserted by button.\n"); // Appends text to a new line
  //   // Or textEdit->insertPlainText("Text inserted by button."); for plain text
  // });








  
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::call_me(){
  std::cout << "im calling from another function";
  
}
  
void MainWindow::on_pushButton_clicked(){
  AdminWindow *adminwindow = new AdminWindow();
  adminwindow->show();
}



// static void fill_a_text()
// {
  // ui->label->setText("New Text After Button Click"); // Change the label text
// }








void MainWindow::on_button_saveUser_clicked()
{
    // Insert button clicked


  a_model->removeRows(ui->listView->currentIndex().row(),1);
  
  
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

