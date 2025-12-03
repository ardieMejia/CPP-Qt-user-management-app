#ifndef USERCSVWIDGET_H
#define USERCSVWIDGET_H


#include <QWidget>
#include <QFile>
#include <QIODevice>
#include <QLabel>
#include <QColor>
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class UserCsvWidget; }
QT_END_NAMESPACE


class UserCsvWidget : public QWidget
{
  Q_OBJECT

  
public:
  UserCsvWidget(QWidget *parent = nullptr);
  ~UserCsvWidget();


private slots:
  void on_uploadUserCsv_clicked();
  void on_validateUserCsv_clicked();
  void on_uploadToDB_clicked();
  void getFile__QStringList(QStringList& files);
					     
public slots:

  


private:
  Ui::UserCsvWidget *ui;
  std::vector<std::vector<std::string>> full_csv;



};

#endif // USERCSVWIDGET_H

