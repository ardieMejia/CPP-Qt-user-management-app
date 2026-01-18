#include <iostream>
#include "deptcsvwidget.h"
#include "ui_deptcsvwidget.h"
#include <QDebug>
#include <vector>
#include <string>
#include <fstream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>




  


DeptCsvWidget::DeptCsvWidget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::DeptCsvWidget)
{
  ui->setupUi(this);

  proceed_csv = true;



  
}

DeptCsvWidget::~DeptCsvWidget()
{
  delete ui;
}






ReadCsvStatus DeptCsvWidget::getFile__QStringList(QStringList& files){
  files = QFileDialog::getOpenFileNames(
						    this,
						    "Select one or more files to open",
						    "./",
						    "Csv (*.csv)");




  if(files.size() > 1){
    QString file = files[0];
    files.clear();
    files.insert(0,file);

    return ReadCsvStatus::MultiFile;
  }else if(files.size() == 1){   
    return ReadCsvStatus::SingleFile;
  }else{
    return ReadCsvStatus::Error;
  }
  

  
}


void DeptCsvWidget::on_uploadDeptCsv_clicked(){



  


  QStringList files = {""};

  
  ReadCsvStatus read_csv_status = getFile__QStringList(files);
  filesystem::path pathCsv("");

  if(read_csv_status == ReadCsvStatus::Error) return;

  if(read_csv_status == ReadCsvStatus::MultiFile){

    std::string fileStatus = "For now multiple upload feature is not supported, please upload a single file \n";
    ui->deptCsvStatusInfo->setStyleSheet("QLabel { color : gray; }");
    ui->deptCsvStatusInfo->setText(QString::fromStdString(fileStatus));
    ui->deptCsvStatus->setText(QString::fromStdString(pathCsv.filename()));

  }else{    
    pathCsv = files[0].toStdString();
    ui->deptCsvStatus->setText(QString::fromStdString(pathCsv.filename()));

  }


  std::string stringPathCsv = pathCsv.string();
  fill_full_csv(stringPathCsv);

    
}





void DeptCsvWidget::fill_full_csv(std::string &pathFile){

  qDebug() << "we first empty our full_csv";
  full_csv.clear();


  std::ifstream file(pathFile);

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


    fields = MyParser::parseCSVRow(line);
    

    // we need to remember in our case, that field is a vector of strings
    
    full_csv.push_back(fields);
  }




}



bool isValidDepartmetId(const std::string& departmentId){
  
    for (char c : departmentId){
	if (!std::isdigit(c)){
	    return false;
	}		
    }
    
    return true;

}


bool isValidDepartmentName(const std::string& departmentName){
  
  std::string departmentName_copy = departmentName;
  
  std::transform(departmentName_copy.begin(), departmentName_copy.end(), departmentName_copy.begin(), ::tolower);
  departmentName_copy.erase(std::remove(departmentName_copy.begin(), departmentName_copy.end(), ' '), departmentName_copy.end());
  
  
  if(std::string("tournamentdirector").find(departmentName_copy) != std::string::npos ||
     std::string("chiefarbiter").find(departmentName_copy) != std::string::npos ||
     std::string("pairingofficer").find(departmentName_copy) != std::string::npos ||
     std::string("scoring&results").find(departmentName_copy) != std::string::npos ||
     std::string("administration&registration").find(departmentName_copy) != std::string::npos ||
     std::string("logistics&venuemanagement").find(departmentName_copy) != std::string::npos ||
     std::string("press&mediarelations").find(departmentName_copy) != std::string::npos){
    qDebug() << "row found";
    return true;
  }
  else{
    qDebug() << "ERROR: there is no such departments for this row";
    return false;
  }
  
  return true;
  
}


// ===== separating upload button is a good idea, coz we have loads to do before that, such as validation, which should be constrained to its own thing
void DeptCsvWidget::on_validateDeptCsv_clicked(){


  if(!proceed_csv) return;
  int i = 0;
  bool doWeCommit = true;

  std::vector<std::string> errorBlock(1, "");
  std::vector<std::string> messageValidErrorBlock(1, "");
  std::string successString("Valid");
  valid_full_csv = true;

  
  // the format we're expecting:
  //
  // | departmentId | departmentName | age |
  // |--------------+----------------+-----|
  // |              |                |     |
  

  for(const auto& row : full_csv){
    i++;
    if(i == 1) continue;



    qDebug() << "department id: " << QString::fromStdString(row[0]);

    if(!isValidDepartmetId(row[0])){

	doWeCommit = false;
	errorBlock = row;
	valid_full_csv = false;
	break;
    }
    if(!isValidDepartmentName(row[1])){

	doWeCommit = false;
	errorBlock = row;
	valid_full_csv = false;
	break;
    }
  }



  std::string errorString("");
  for(const auto& block : errorBlock){
    errorString += block;
  }



  ui->validateCsvStatus->setText(QString::fromStdString(errorString));
  ui->validateCsvStatusTitle->setStyleSheet("QLabel { font_weight: bold;}");

  qDebug() << "error string" << QString::fromStdString(errorString);


  if(errorString != ""){
    ui->validateCsvStatus->setText(QString::fromStdString(errorString));
    ui->validateCsvStatus->setStyleSheet("QLabel { color : rgb(255, 105, 0);}");    
  }else{
    ui->validateCsvStatus->setText(QString::fromStdString(successString));
    ui->validateCsvStatus->setStyleSheet("QLabel { color : rgb(25, 135, 84);}");        
  }
    

 }











void DeptCsvWidget::on_uploadToDB_clicked(){


  ui->uploadToDBStatus->setText("");
  if(!valid_full_csv){
    ui->uploadToDBStatus->setStyleSheet("QLabel { color : rgb(255, 105, 0);}");    
    ui->uploadToDBStatus->setText("Commit to DB failed, invalid CSV");    
    return;
  }


  QSqlDatabase db = QSqlDatabase::database("_render_connection_db");
  QSqlQuery query(db);

  QString lastQueryStatus("no query committed");

  
  int i = 0;
  for(const auto& row : full_csv){
    
    i++;
    if(i == 1) continue;
    query.prepare("INSERT INTO departments (department_name) "
		  "VALUES (:department_name)");
    QString departmentName = QString::fromStdString(row[1]);

    query.bindValue(":department_name", departmentName);

    
    bool result = query.exec();
    
    
    if(result){
      qDebug() << "fine";
    }else{
      lastQueryStatus = query.executedQuery();      
    }
    QSqlError error = query.lastError();
    qDebug() << error;


  }


  ui->uploadToDBStatus->setText(lastQueryStatus);

  

  
  

  
}




