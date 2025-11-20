#include "userupdatewidget.h"
#include "ui_userupdatewidget.h"
#include <QDebug>
#include <QSqlDatabase>


#include "database.h"

UserUpdateWidget::UserUpdateWidget(QWidget *parent, int indexDepartment)
  : QWidget(parent)
  , ui(new Ui::UserUpdateWidget)
  , m_indexDepartment(indexDepartment)
    
{
  ui->setupUi(this);




  // testModel = new QStringListModel(this);
  // QStringList list2;
  // list2 << "Hanifa" << "Bev" << "Ardie";
  // testModel->setStringList(list2);
  
  // ui->tableSingleUserView->setModel(testModel);





  QSqlDatabase db = QSqlDatabase::database("_render_connection_db");



  if(db.open() && db.isValid()){    
    QSqlQuery queryDepartment(db);
    
    queryDepartment.prepare("SELECT * FROM departments");
    queryDepartment.exec();
    
    modelDepartment = new QSqlQueryModel();
    modelDepartment->setQuery(queryDepartment);

    
    QSqlQuery queryUser(db);
    
    // queryUser.prepare("SELECT  FROM users");

    queryUser.prepare("SELECT * FROM users WHERE id = :id");
    // queryUser.bindValue(":name", values.at(1));
    // queryUser.bindValue(":age", values.at(2));
    qDebug() << indexDepartment;
    queryUser.bindValue(":id", indexDepartment);

    

    queryUser.exec();
    
    modelUser = new QSqlQueryModel();
    modelUser->setQuery(queryUser);


    
    // testModel = new QStringListModel(this);
    // QStringList list2;
    // list2 << "Hanifa" << "Bev" << "Ardie";
    // testModel->setStringList(list2);
    
    ui->userNameLineEdit->setText(modelUser->record(0).field("name").value().toString());

    // QAbstractItemModel *testmodel = index.model();
    // testModel = new QAbstractItemModel();

    
      
    ui->userDepartmentComboBox->setItemText(0,"asd");
    ui->userDepartmentComboBox->setCurrentIndex(0);
      // setText(modelUser->record(0).field("name").value().toString());
    

    qDebug() << modelDepartment->rowCount();
    
    testModel = new QStringListModel(this);
    
    QStringList list2;
    for(int i=0; i < modelDepartment->rowCount();i++){
      list2 << "Hanifa";      
    }

    testModel->setStringList(list2);

    // ui->userDepartmentComboBox->setItemText(0,"asd");
    // ui->userDepartmentComboBox->setCurrentIndex(0);

    ui->userDepartmentComboBox->setModel(testModel);
    ui->userDepartmentComboBox->setCurrentIndex(2);    
    

    
  }

  







  
}


UserUpdateWidget::~UserUpdateWidget()
{
  delete ui;
}
