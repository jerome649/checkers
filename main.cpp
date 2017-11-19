#include <iostream>
#include "checkers_board.hpp"

int main() {
  std::cout << "Checkers" << std::endl;
  CheckersBoard* checkers_board = new CheckersBoard(10);
  checkers_board->print();

  delete checkers_board;
  return 0;
}
