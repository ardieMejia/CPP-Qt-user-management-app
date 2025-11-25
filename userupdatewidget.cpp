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









  QSqlDatabase db = QSqlDatabase::database("_render_connection_db");



  if(db.open() && db.isValid()){    
    QSqlQuery queryDepartment(db);
    
    queryDepartment.prepare("SELECT * FROM departments");
    queryDepartment.exec();
    
    modelDepartment = new QSqlQueryModel();
    modelDepartment->setQuery(queryDepartment);

    
    QSqlQuery queryUser(db);
    

    queryUser.prepare("SELECT * FROM users WHERE id = :id");
    qDebug() << indexDepartment;
    queryUser.bindValue(":id", indexDepartment);

    

    queryUser.exec();
    
    modelUser = new QSqlQueryModel();
    modelUser->setQuery(queryUser);


    

    
    ui->userNameLineEdit->setText(modelUser->record(0).field("name").value().toString());



    
      
    ui->userDepartmentComboBox->setItemText(0,"asd");
    ui->userDepartmentComboBox->setCurrentIndex(0);
      // setText(modelUser->record(0).field("name").value().toString());
    


    // ===== old simple example
    modelCombo1 = new QStringListModel(this);    
    QStringList list2;
    for(int i=0; i < modelDepartment->rowCount();i++){
      list2 << modelDepartment->record(i).field("department_name").value().toString();
    }
    modelCombo1->setStringList(list2);
    ui->userDepartmentComboBox->setModel(modelCombo1);
    ui->userDepartmentComboBox->setCurrentIndex(2);
    // ===== old simple example



    modelCombo2 = new QStandardItemModel(this);
    for(int i=0; i < modelDepartment->rowCount();i++){
      QString itemDeptName;
      int itemId;
      itemDeptName = modelDepartment->record(i).field("department_name").value().toString();
      itemId = modelDepartment->record(i).field("id").value().toInt();
      modelCombo2->appendRow(new QStandardItem(itemDeptName));
      modelCombo2->setData(modelCombo2->index(0, 0), itemId, Qt::UserRole); // Store a custom ID
    }


    

    
  }

  







  
}


UserUpdateWidget::~UserUpdateWidget()
{
  delete ui;
}
