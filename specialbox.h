#ifndef SPECIALBOX_H
#define SPECIALBOX_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class NewBox; }
QT_END_NAMESPACE

class NewBox : public QWidget
{
  Q_OBJECT

public:
  NewBox(QWidget *parent = nullptr);
  ~NewBox();

/* private slots: */
/*   void on_pushButton_clicked(); // Slot for a button named 'myButton' */


private:
  Ui::NewBox *ui;
  
};
#endif // SPECIALBOX_H
