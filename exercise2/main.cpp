
//#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  int input;
  do{
    std::cout << "Lasd Libraries 2024" << std::endl;
    std::cout << "0 - run lasdtest" << std::endl << "1 - run mytest" << std::endl;
    std::cin >> input;
    if (input != 0 && input != 1) std::cout << "input non valido" << std::endl;
  } while (input != 0 && input != 1);

  // if (input == 0) lasdtest();
  // else if (input == 1) mytest();

  return 0;
}
