#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
  // connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onButtonClicked;

  // ui->label->setText("hello hello");
  // ui->label->setText("hello hello");

  ui->label->setText("helloooo");
  
  myLabel = new QLabel("Click Me", this);
  myLabel->setGeometry(100, 100, 150, 30); // x, y, width, height
  
  QObject::connect(ui->pushButton, &QPushButton::clicked, [&]() {
    ui->textEdit->append("Text inserted by button.\n"); // Appends text to a new line
    // Or textEdit->insertPlainText("Text inserted by button."); for plain text
  });
  
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  // Accessing a QLabel named 'myLabel'
  ui->label->setText("Button clicked!");
  ui->textEdit->append("Text inserted by button.\n"); // Appends text to a new line


}


// static void fill_a_text()
// {
  // ui->label->setText("New Text After Button Click"); // Change the label text
// }

// QObject::connect(pushButton, &QPushButton::clicked, [textEdit]() {
//   textEdit->append("Text inserted by button.\n"); // Appends text to a new line
//   // Or textEdit->insertPlainText("Text inserted by button."); for plain text
//  });


