#include <database.h>
#include <iostream> // For error reporting
#include <string> // Includes the standard string class
// #include <QVariant>








bool isUsersTableFilled = false;


QVariant _openDatabase(){
  
  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "_render_connection_db");


  db.setHostName("dpg-d37auere5dus739709qg-a.singapore-postgres.render.com");
  db.setPort(5432); // Default PostgreSQL port
  db.setDatabaseName("vanilla_postgresql_1");
  db.setUserName("vanilla_postgresql_1_user");
  db.setPassword("2hiE2Y8h6GQr9vpnvcd71PS1WBDWsEi4");

  qDebug() << "attempting to connect";

  if (!db.open()) {
    QVariant errorString = "Error: Failed to connect to database:" + db.lastError().text();
    return errorString;
  } else {


    QVariant successString = "Connected to database!";
    return successString;
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
