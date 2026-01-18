
#include <iostream>
#include "usercsvwidget.h"
#include "ui_usercsvwidget.h"
#include <QDebug>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>




  


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









ReadCsvStatus UserCsvWidget::getFile__QStringList(QStringList& files){
  files = QFileDialog::getOpenFileNames(
						    this,
						    "Select one or more files to open",
						    "./",
						    "Csv (*.csv)");




  if (files.size() > 1){
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


void UserCsvWidget::on_uploadUserCsv_clicked()
{

  QStringList files = {""};

  
  ReadCsvStatus read_csv_status = getFile__QStringList(files);
  filesystem::path pathCsv("");

  if(read_csv_status == ReadCsvStatus::Error) return;

  if(read_csv_status == ReadCsvStatus::MultiFile){

    std::string fileStatus = "For now multiple upload feature is not supported, please upload a single file \n";
    ui->userCsvStatusInfo->setStyleSheet("QLabel { color : gray; }");
    ui->userCsvStatusInfo->setText(QString::fromStdString(fileStatus));
    ui->userCsvStatus->setText(QString::fromStdString(pathCsv.filename()));

  }else{
    
    pathCsv = files[0].toStdString();
    ui->userCsvStatus->setText(QString::fromStdString(pathCsv.filename()));

  }


  std::string stringPathCsv = pathCsv.string();
  fill_full_csv(stringPathCsv);

    
}





void UserCsvWidget::fill_full_csv(std::string &pathFile){

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



bool isValidUserName(const std::string& name) {

    for (char c : name){
	if (std::isdigit(c)){
	    return false;
	}		
    }

    
    return true;
}


bool isValidUserId(const std::string& userId) {

    for (char c : userId){
	if (!std::isdigit(c)){
	    return false;
	}		
    }



    
    return true;
}
bool isValidAge(const std::string& age) {

    for (char c : age){
	if (!std::isdigit(c)){
	    return false;
	}		
    }

    if (QString::fromStdString(age).toInt() >= 3000){
      return false;
    }

    
    return true;
}


bool isValidUserDepartmentName(const std::string& departmentName) {
  

  std::string departmentName_copy = departmentName;
  
  std::transform(departmentName_copy.begin(), departmentName_copy.end(), departmentName_copy.begin(), ::tolower);
  departmentName_copy.erase(std::remove(departmentName_copy.begin(), departmentName_copy.end(), ' '), departmentName_copy.end());
  
  
  if(std::string("tournamentdirector").find(departmentName_copy) != std::string::npos ||
     std::string("chiefarbiter").find(departmentName_copy) != std::string::npos ||
     std::string("pairingofficer").find(departmentName_copy) != std::string::npos ||
     std::string("scoring&results").find(departmentName_copy) != std::string::npos ||
     std::string("administration&registration").find(departmentName_copy) != std::string::npos ||
     std::string("logistics&venuemanagement").find(departmentName_copy) != std::string::npos ||
     std::string("press&mediarelations").find(departmentName_copy) != std::string::npos ||
     std::string("none").find(departmentName_copy) != std::string::npos){
    qDebug() << "row found";
    return true;
  }
  else{
    qDebug() << "ERROR: there is no such departments for this row";
    return false;
  }
  
  
  return true;

}


std::string toCleanUserDepartmentName(const std::string& departmentName){
  
  
  std::string departmentName_copy = departmentName;
  
  std::transform(departmentName_copy.begin(), departmentName_copy.end(), departmentName_copy.begin(), ::tolower);
  
  
  if(std::string("tournament director").find(departmentName_copy) != std::string::npos){      
    return "tournament director";
  }
  else if(std::string("chief arbiter").find(departmentName_copy) != std::string::npos){
    return "chief arbiter";    
  }
  else if(std::string("pairing officer").find(departmentName_copy) != std::string::npos){
    return "pairing officer";    
  }
  else if(std::string("scoring & results").find(departmentName_copy) != std::string::npos){
    return "scoring & results";    
  }
  else if(std::string("administration & registration").find(departmentName_copy) != std::string::npos){
    return "administration & registration";    
  }
  else if(std::string("logistics & venue management").find(departmentName_copy) != std::string::npos){
    return "logistics & venue management";    
  }
  else if(std::string("press & media relations").find(departmentName_copy) != std::string::npos){
    return "press & media relations";    
  }
  else if(std::string("none").find(departmentName_copy) != std::string::npos){
    return "none";    
  } 
  
  else{
    qDebug() << "ERROR: there is no such departments for this row";
    return "none";
  }
  
    
  return "none";
  
}


// ===== separating upload button is a good idea, coz we have loads to do before that, such as validation, which should be constrained to its own thing
void UserCsvWidget::on_validateUserCsv_clicked(){


  int i = 0;
  bool doWeCommit = true;

  std::vector<std::string> errorBlock;
  std::string successString("Valid");
  valid_full_csv = true;

  // the format we're expecting:
  //
  // | userId | userName | age | departmentName |
  // |--------+----------+-----+----------------|
  // |        |          |     |                |
  



  
  for(const auto& row : full_csv){
    i++;
    if(i == 1) continue;



    qDebug() << "fideid: " << QString::fromStdString(row[0]);
    
    if(!isValidUserId(row[0])){
      
      doWeCommit = false;
      errorBlock = row;
      valid_full_csv = false;
      break;
    }
    if(!isValidUserName(row[1])){
      
      doWeCommit = false;
      errorBlock = row;
      valid_full_csv = false;
      break;
    }
    if(!isValidAge(row[2])){
      
      doWeCommit = false;
      errorBlock = row;
      valid_full_csv = false;
      break;
    }
    if(!isValidUserDepartmentName(row[3])){
      
      qDebug() << "department name after validation " << QString::fromStdString(row[3]);
      doWeCommit = false;
      errorBlock = row;
      valid_full_csv = false;
      break;
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
    


    
  }




  std::string errorString("");
  for(const auto& block : errorBlock){
    errorString += block;
  }



  ui->validateCsvStatus->setText(QString::fromStdString(errorString));
  ui->validateCsvStatusTitle->setStyleSheet("QLabel { font_weight: bold;}");

  qDebug() << "error string" << QString::fromStdString(errorString);

  // if error sring is not empty
  if(errorString != ""){
    ui->validateCsvStatus->setText(QString::fromStdString(errorString));
    ui->validateCsvStatus->setStyleSheet("QLabel { color : rgb(255, 105, 0);}");    
  }else{
    ui->validateCsvStatus->setText(QString::fromStdString(successString));
    ui->validateCsvStatus->setStyleSheet("QLabel { color : rgb(25, 135, 84);}");        
  }


  
}











void UserCsvWidget::on_uploadToDB_clicked(){


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
    
    // ==================================================
    

    QString id;
    std::string departmentName_clean = toCleanUserDepartmentName(row[3]);
    qDebug() << "clean department name" << QString::fromStdString(departmentName_clean);
    QSqlQuery query_getDepartmentId(db);
    query_getDepartmentId.prepare("SELECT * FROM departments WHERE LOWER(department_name) = :departmentName_clean");

    query_getDepartmentId.bindValue(":departmentName_clean",QString::fromStdString(departmentName_clean));

    // if( query_getDepartmentId.exec ()) {
    //   query_getDepartmentId.first();
    //   qDebug() << query_getDepartmentId.record ().value(0);
    // }

    QString departmentId;
    if(query_getDepartmentId.exec()) {
      qDebug() << "we are here" << "\n";
      if(query_getDepartmentId.first()){	
	int fieldIndex = query_getDepartmentId.record().indexOf("id");
	qDebug() << "fieldIndex" << fieldIndex;
	qDebug() << "isvalid" << query_getDepartmentId.isValid();
	departmentId = query_getDepartmentId.value(0).toString();
	qDebug() << "going in" << "\n";
	qDebug() << departmentId;
      }
    }
    
    qDebug() << "last select from parent query" << query_getDepartmentId.executedQuery();

    // ==================================================       
    query.prepare("INSERT INTO users (name, age) "
		  "VALUES (:name,:age)");
    QString name = QString::fromStdString(row[1]);
    QString age = QString::fromStdString(row[2]);



    bool ok = 1;
    int  ageNum = age.toInt(&ok);
    if(!ok){      
      ui->uploadToDBStatus->setStyleSheet("QLabel { color : rgb(255, 105, 0);}");    
      ui->uploadToDBStatus->setText("converting age to integer failed");
      return;
    }
    ok = 1;
    int  departmentIdNum = departmentId.toInt(&ok);
    if(!ok){      
      ui->uploadToDBStatus->setStyleSheet("QLabel { color : rgb(255, 105, 0);}");    
      ui->uploadToDBStatus->setText("converting departmentId to integer failed");
      return;
    }
    query.bindValue(":name", name);
    query.bindValue(":age", ageNum);
    query.bindValue(":department_id", departmentId);
    
    bool result = query.exec();
    
    
    if(result){
      qDebug() << "fine";
    }else {
      lastQueryStatus = query.executedQuery();
    }
    QSqlError error = query.lastError();
    qDebug() << error;


  }


  ui->uploadToDBStatus->setText(lastQueryStatus);


  qDebug() << "last query" << query.executedQuery();

  

  
  

  
}




