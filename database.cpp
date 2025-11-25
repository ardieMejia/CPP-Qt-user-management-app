#include <database.h>
#include <iostream> // For error reporting
#include <string> // Includes the standard string class
#include <stdexcept> // For std::stoi and related exceptions
#include <QByteArray>
#include <QDebug>

// #include <QVariant>







DBconnectionStatus g_current_connection_status = {false, ""};











bool isDepartmentTableFilled = false;



DBconnectionStatus _openDatabase(){
  
  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "_render_connection_db");



  // QString qt_hostname = ;
  qDebug() << "hello";
  db.setHostName(QString::fromLocal8Bit(qgetenv("QT_HOSTNAME")));
  bool ok;
  qDebug() << qgetenv("QT_HOSTNAME");
  db.setPort(qgetenv("QT_PORT").toInt(&ok, 10));
  db.setDatabaseName(QString::fromLocal8Bit(qgetenv("QT_DATABASENAME")));
  db.setUserName(QString::fromLocal8Bit(qgetenv("QT_USERNAME")));
  db.setPassword(QString::fromLocal8Bit(qgetenv("QT_PASSWORD")));
  // return {false, "oops"};

      // QByteArray pathValue = qgetenv("PATH");

  qDebug() << "attempting to connect";

  if (!db.open()) {
    std::string errorString = "Error: Failed to connect to database:" + db.lastError().text().toStdString();
    qDebug() << "oops";
    return {false, errorString};
  } else {


    std::string successString = "Connected to database!";
    return {true, successString};
  }
  db.close();


  // ========== temp
  // QVariant errorString = "Error: Failed to connect to database:";
  // return errorString;
}

// void _closeDatabase() {
//   if (db) {
//     db->close(); 
//   }
// }
