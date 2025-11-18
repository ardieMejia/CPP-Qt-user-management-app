#include "specialbox.h"
#include "ui_specialBox.h"
#include <qpushbutton.h>



NewBox::NewBox(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::NewBox)
    
{
  ui->setupUi(this);


  
  // connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onButtonClicked;

  // ui->label->setText("hello hello");
  // ui->label->setText("hello hello");

  // ui->label->setText("helloooo");
  
  // QObject::connect(ui.pushButton, &QPushButton::clicked, [&]() {
  //   ui.textEdit->append("Text inserted by button.\n"); // Appends text to a new line
  //   // Or textEdit->insertPlainText("Text inserted by button."); for plain text
  // });
  
}

NewBox::~NewBox()
{
  delete ui;
}




// static void fill_a_text()
// {
  // ui->label->setText("New Text After Button Click"); // Change the label text
// }

// QObject::connect(pushButton, &QPushButton::clicked, [textEdit]() {
//   textEdit->append("Text inserted by button.\n"); // Appends text to a new line
//   // Or textEdit->insertPlainText("Text inserted by button."); for plain text
//  });



