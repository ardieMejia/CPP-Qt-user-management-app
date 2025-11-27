


// Computes and prints n! for a given n.
// Uses several basic elements of C++.
#include <iostream>
#include <child/hello.h>
#include <child/hello2.h>
#include <cctype>
#include <tuple>
#include <string>


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


int main() {
  using namespace std;
  /* Declarations of variables */
  std::string factArg;
  int factorial_arg;
  std::tuple<bool, int, std::string> toNumbers_val();
  
  int fact (1);
  bool cont_ask;
  do {
    cout << "Factorial of: ";
    cin >> factArg;
    std::tuple<bool,int,std::string> toNumbers_val = toNumbers(factArg);
    cont_ask = std::get<0>(toNumbers_val);
      if(!cont_ask) {
      cout << "Numbers only please" << endl;
      }else{
	factorial_arg = std::get<1>(toNumbers_val);
      }
  } while(!cont_ask) ;
  int i = 2;
  while( i <= factorial_arg ) {
    fact = fact * i;
    i = i + 1;
  }
  cout << "The Factorial of " << factorial_arg << " is: " << fact << endl;
  return 0;
}
