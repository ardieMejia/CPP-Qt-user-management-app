#include <iostream>
#include "usercsvwidget.h"
#include "ui_usercsvwidget.h"
#include <QDebug>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>




  


UserCsvWidget::UserCsvWidget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::UserCsvWidget)
{
  ui->setupUi(this);



  
}

UserCsvWidget::~UserCsvWidget()
{
  delete ui;
}













void UserCsvWidget::getFile__QStringList(QStringList& files){
  files = QFileDialog::getOpenFileNames(
						    this,
						    "Select one or more files to open",
						    "/home",
						    "Images (*.png *.xpm *.jpg)");


  qDebug() << files;
  for (const auto& file : files){      
    qDebug() << file;
  }

  if (files.size() > 1){
    qDebug() << "for now multiple upload feature is not supported, please upload a single file";
    // return QStringList(QString::fromStdString(""));
  }

  // return files;
  
}


void UserCsvWidget::on_uploadUserCsv_clicked()
{


  

  // ===== this is a stupid test =====
  QStringList files = {""};				 
							 
  QString* test = new QString();			 
  QString* an_address = test;				 
  qDebug() << an_address;				 
							 
  int i = 123;						 
  int* an_address2 = &i;				 
  qDebug() << an_address2;				 
							 
							 
  // remember RAII					 
  std::string* j = new std::string("hello there");	 
  std::string* k = new std::string("goodbye");		 
  qDebug() << "1st pointer" << &j;			 
  qDebug() << "2nd pointer" << &k;			 
  j = k;						 
  qDebug() << "1st pointer" << &j;			 
  // ==================================================  
  

  getFile__QStringList(files);
    
}













bool isValidName(const std::string& name) {


    for (char c : name){
	if (std::isdigit(c)){
	    return false;
	}		
    }

    
    return true;
}


// ===== separating upload button is a good idea, coz we have loads to do before that, such as validation, which should be constrained to its own thing
void UserCsvWidget::on_validateUserCsv_clicked(){


  int i = 0;

  std::vector<std::string> errorBlock(1, "");
  for(const auto& row : full_csv){
    i++;
    if(i == 1) continue;

    bool doWeAppend = false;


	// this is not a name!!
    if(!isValidName(row[0])){
	doWeAppend = true;
    }

    
    


    
    

    
    if(doWeAppend){
	errorBlock = row;	
    }


    
  }

  qDebug() << "what" << QString::fromStdString(errorBlock[0]);


  ui->validateCsvStatusTitle->setText("Invalid Data");
  ui->validateCsvStatusTitle->setStyleSheet("QLabel { font-weight: bold;}");
  ui->validateCsvStatus->setText(QString::fromStdString(errorBlock[0]));
  ui->validateCsvStatus->setStyleSheet("QLabel { color : rgb(255, 105, 0);}");








  
}











void UserCsvWidget::on_uploadToDB_clicked(){


  // we are always using the same connection, so this is fine
  // QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
  // QSqlQuery query(db);
  // query.prepare("INSERT INTO users (name, age) "
  // 		"VALUES (:name, :age)");
  // QString name = ui->textEditName->toPlainText();
  // QString age = ui->textEditAge->toPlainText();
  // query.bindValue(":name", name);
  // query.bindValue(":age", age);
  // bool result = query.exec();
  

  // if(result){
  //   qDebug() << "fine";
  // }
  // QSqlError error = query.lastError();
  // qDebug() << error;

  
}




