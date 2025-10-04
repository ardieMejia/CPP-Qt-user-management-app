


// Computes and prints n! for a given n.
// Uses several basic elements of C++.
#include <iostream>
#include <child/hello.h>
#include <child/hello2.h>
#include <cctype>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <tuple>
#include <string>

#include <QApplication> // Required for the application object
#include <QMainWindow>
#include <QWidget>      // Required for the base window widget
#include <QLabel>      // Required for the base window widget
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "table.h"
// #include "ui_mainwindow.h"



// #include <QCoreApplication>




std::string filterNumbers(const std::string& inputString) {
  std::string filteredString;
  for (char c : inputString) {
    if (std::isdigit(c)) {
      filteredString += c;
    }
  }
  return filteredString;
}



std::tuple<bool, int, std::string> toNumbers(const std::string& inputString) {
  int converted_int;
  try {
    converted_int = std::stoi(inputString);
    return std::make_tuple(true, converted_int, "nothing");
  } catch (const std::invalid_argument& e) {
    return std::make_tuple(false, 0, e.what()) ;
  } catch (const std::out_of_range& e) {
    return std::make_tuple(false, 0, e.what());
  }
}




int main(int argc, char *argv[])
{
  
  // template <typename T> std::string type_name();
  // Create a QApplication object. This is the central object for Qt applications,
  // managing application-wide resources and the event loop.
  QApplication app(argc, argv);


  




  MainWindow widget;
  // MainWindow widget;
  widget.show();
  // widget.show();






  return app.exec();
}

