#include <iostream>
#include "mainwindow.h"
#include "table.h"
#include "ui_mainwindow.h"
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

  

  ui->label->setText("helloooo");
  
  myLabel = new QLabel("Click Me", this);
  myLabel->setGeometry(100, 100, 150, 30); // x, y, width, height
  
  QObject::connect(ui->pushButton, &QPushButton::clicked, [&]() {
    ui->textEdit->append("Text inserted by button.\n"); // Appends text to a new line
    // Or textEdit->insertPlainText("Text inserted by button."); for plain text
  });



  TableModel *tablemodel = new TableModel(this);
  // tablemodel->

  // tablemodel->setHeaderData(1, Qt::Horizontal, *v, Qt::DisplayRole)

  if(!tablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"), Qt::DisplayRole))
    qDebug() << "unable to set header";
  if(!tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("Genre"), Qt::DisplayRole))
    qDebug() << "unable to set header";
  if(!tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("Project"), Qt::DisplayRole))
    qDebug() << "unable to set header";

  // ok = tablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("Amount"));
  // ok = tablemodel->setHeaderData(2, Qt::Horizontal, QObject::tr("Amount"));
      // if( ! model->setHeaderData(0, Qt::Horizontal, *v) )
      // 	qDebug() << "Set hdr failed";
  tablemodel->addRow({"Data A1", "Data B1", "Data C1"});
  tablemodel->addRow({"Data A2", "Data B2", "Data C2"});
  tablemodel->addRow({"Data A3", "Data B3", "Data C3"});
  QVariant *example = new QVariant(QString("Some text"));
  tablemodel->setData(0,0,*example);


  ui->tableView->setModel(tablemodel);


  
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::call_me(){
  std::cout << "im calling from another function";
  
}
  
void MainWindow::on_pushButton_clicked()
{
  // Accessing a QLabel named 'myLabel'
  ui->textEdit->append("Text inserted by button.\n"); // Appends text to a new line



  ui->label->setAlignment(Qt::AlignTop);
    
  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

  // db.setHostName("localhost"); // or your PostgreSQL server IP
		 // postgresql://mcf_postgresql_2_f0js_user:uiIxeWWFoDcSRipK9BhSEqmTYxZ5jMCW@dpg-d288ja49c44c73a6oi5g-a.singapore-postgres.render.com/mcf_postgresql_2_f0js
  db.setHostName("dpg-d288ja49c44c73a6oi5g-a.singapore-postgres.render.com");
  db.setPort(5432); // Default PostgreSQL port
  db.setDatabaseName("mcf_postgresql_2_f0js");
  db.setUserName("mcf_postgresql_2_f0js_user");
  db.setPassword("uiIxeWWFoDcSRipK9BhSEqmTYxZ5jMCW");

  qDebug() << "attempting to connect";

  if (!db.open()) {
    qDebug() << "Error: Failed to connect to database:" << db.lastError().text();
    return;
  } else {
    // qDebug() << "Connected to database!";
    ui->label->setText("Connected to database!");
  }

  
  QSqlQuery query(db);

  if (query.exec("SELECT id, \"tournamentName\"  FROM events")) {
    while (query.next()) {
      int id = query.value(0).toInt();
      QString tournamentName = query.value(1).toString();
      QString startDate = query.value(2).toString();
      QString endDate = query.value(3).toString();
      qDebug() << "ID:" << id << "tournament name:" << tournamentName << "start date:" << startDate
	       << "end data";
    }
  } else {
    qDebug() << "Error selecting data:" << query.lastError().text();
  }
  
  
  
  
  db.close(); 


}


// static void fill_a_text()
// {
  // ui->label->setText("New Text After Button Click"); // Change the label text
// }

// QObject::connect(pushButton, &QPushButton::clicked, [textEdit]() {
//   textEdit->append("Text inserted by button.\n"); // Appends text to a new line
//   // Or textEdit->insertPlainText("Text inserted by button."); for plain text
//  });






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
  QModelIndex tp_index = ui->listView->currentIndex();

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

}

