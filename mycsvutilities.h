#ifndef MYCSVUTILITIES_H
#define MYCSVUTILITIES_H

#include <iostream>
#include <QDebug>
#include <vector>
#include <string>


enum class ReadCsvStatus{
  Error = -1,
  SingleFile = 0,
  MultiFile = 1,
  
};

namespace MyParser {
  std::vector<std::string> parseCSVRow(const std::string& row);
}



#endif // MYCSVUTILITIES_H
