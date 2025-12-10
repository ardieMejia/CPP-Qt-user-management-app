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




void UserCsvWidget::empty_function(){

  qDebug() << "this function does nothing";

}




void UserCsvWidget::_on_uploadUserCsv_clicked(){
  QFile f("./data.csv");

  if(!f.open(QIODevice::ReadOnly)){
    ui->userCsvStatus->setText(QString::fromStdString("cant read file"));

  }

  while(!f.atEnd()){
    QByteArray line = f.readLine();
    QList<QByteArray> fields = line.split(',');
    qDebug() << fields.size();
    qDebug() << line;
  }

  
}


std::vector<std::string> parseCSVRow(const std::string& row) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;
    
    for (char c : row) {
        if (!inQuotes && c == ',') {
            fields.push_back(field);
            field.clear();
        } else if (c == '"') {
            inQuotes = !inQuotes;
        } else {
            field += c;
        }
    }
    fields.push_back(field);
    
    return fields;
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
  // WordCountDialog dialog(this);
  // dialog.setWordCount(document().wordCount());
  // qDebug() << "we are a dialog";
  // dialog.exec();
  
  // QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
  //                        "/home/jana/untitled.png",
  //                        tr("Images (*.png *.xpm *.jpg)"));

  
  
  // AdminWindow *adminwindow = new AdminWindow(this);


  

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





void UserCsvWidget::__on_uploadUserCsv_clicked(){

  qDebug() << "lets declare an empty vector of strings";

  // std::vector<std::string> some_shit;

  // declaer data as vector of vector of string
  // std::vector<std::vector<std::string>> full_csv;

  std::ifstream file("./data.csv");

  if(!file.is_open()){
    qDebug() << "cant read file, something went wrong";
  }

  // ===== using getline means we dont have to deal with \n

  std::string line;

  while(std::getline(file, line)){
    // std::vector<std::string> row;
    std::vector<std::string> fields;
    // std::stringstream ss(line);
    std::string cell;


    fields = parseCSVRow(line);
    

    // we need to remember in our case, that field is a vector of strings
    
    full_csv.push_back(fields);
  }



  for(const auto& a_row : full_csv){
    for(const std::string& a_cell : a_row) {
        qDebug() << "something should be here";
        std::string someshit;
        someshit = someshit + a_cell;
      
        qDebug() << "someshit" << QString::fromStdString(someshit);
        qDebug() << "a_cel" << QString::fromStdString(a_cell);
    }
  }
}







bool isValidName(const std::string& name) {
    // std::vector<std::string> fields;
    // std::string field;
    // bool inQuotes = false;
    
    // for (char c : row) {
    //     if (!inQuotes && c == ',') {
    //         fields.push_back(field);
    //         field.clear();
    //     } else if (c == '"') {
    //         inQuotes = !inQuotes;
    //     } else {
    //         field += c;
    //     }
    // }
    // fields.push_back(field);

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

    
    
    // for(const auto& field : row){
    //   for(const auto& c : field){
    // 	std::string isdigit = "false";
    // 	qDebug() << "field: " << QString::fromStdString(field);
    // 	if(std::isdigit(c)){
    // 	  isdigit = "true";
    // 	}
      
    //   }
      
    // }

    
    
    // for (const auto& field : row){
    //   qDebug() << QString::fromStdString(field);
    // }
    
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




