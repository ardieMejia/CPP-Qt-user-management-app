#ifndef DEPTCSVWIDGET_H
#define DEPTCSVWIDGET_H


#include <QWidget>
#include <QFile>
#include <QIODevice>
#include <QLabel>
#include <QColor>
#include <QFileDialog>
#include <filesystem>
#include <mycsvutilities.h>


using namespace std;





QT_BEGIN_NAMESPACE
namespace Ui { class DeptCsvWidget; }
QT_END_NAMESPACE


class DeptCsvWidget : public QWidget
{
  Q_OBJECT

  
public:
  DeptCsvWidget(QWidget *parent = nullptr);
  ~DeptCsvWidget();


private slots:
  void on_uploadDeptCsv_clicked();
  void fill_full_csv(std::string &pathFile);
  void on_validateDeptCsv_clicked();
  void on_uploadToDB_clicked();
  ReadCsvStatus getFile__QStringList(QStringList& files);
					     
public slots:

  


private:
  Ui::DeptCsvWidget *ui;
  std::vector<std::vector<std::string>> full_csv;
  bool valid_full_csv;
  bool proceed_csv;



};

#endif // DEPTCSVWIDGET_H

