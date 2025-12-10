


// Computes and prints n! for a given n.
// Uses several basic elements of C++.
#include <iostream>

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
#include <QDebug>



// #include "ui_mainwindow.h"



// #include <QCoreApplication>












int main(int argc, char *argv[])
{
  
  // template <typename T> std::string type_name();
  // Create a QApplication object. This is the central object for Qt applications,
  // managing application-wide resources and the event loop.



    QList<QString> testlist = {"1", ":2014"};

    QStringList testlist_better(testlist);
    QStringList testlist_better2(QList<QString>({"!", "2"}) );

    for (const auto& elementString : testlist_better){
      qDebug() << elementString;
    }
    for (const auto& elementString : testlist_better2){
      qDebug() << elementString;
    }
  



    int x;

    std::cout << "type a number";
    std::cin >> x;
    std::cout << "your number is:";
    std::cout << x;


    int *ptr;
    ptr = (int*) malloc(sizeof(int));



    



    

    // word1 is the string we want
    
    const char *word1 = "Tournament";
    const char *word2 = "Tournament Director";
    
    int resultc = strcmp(word1, word2);

    std::cout << "\n";
    std::cout << "compare (0 is same): " << resultc;


    std::string sword1(word1);
    std::string sword2(word2);
    

    // int result = sword2.find(sword1);

    if(std::string(word1).find(sword1) == std::string::npos){
      std::cout << "CANT find sword1 in sword2";
    }else{
      std::cout << "match";
    }



    std::transform(sword2.begin(), sword2.end(), sword2.begin(), ::tolower);
    sword2.erase(std::remove(sword2.begin(), sword2.end(), ' '), sword2.end());

    std::cout << sword2;


    std::string departmentName = "something normal";


    std::cout << "\n original: ";
    std::cout << departmentName;

      
    std::string departmentName_copy = departmentName;
    departmentName_copy += "asdasd";

    
    std::cout << "\n original: ";
    std::cout << departmentName;
    std::cout << "\n copy: ";
    std::cout << departmentName_copy;

    
}

