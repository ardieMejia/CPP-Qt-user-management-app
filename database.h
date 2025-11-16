#pragma once // Ensures the header is included only once



#include <QSqlDatabase>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>




extern QSqlDatabase db;
/* extern bool isUsersTableFilled; */

struct DBconnectionStatus {
  bool status = false;
  std::string statusString = "";
};

DBconnectionStatus _openDatabase();
