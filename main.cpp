#include <iostream>
#include "checkers_board.hpp"
#include "checkers_node.hpp"
#include "checkers_move.hpp"

int main() {
  std::cout << "Checkers" << std::endl;
  CheckersBoard* checkers_board = new CheckersBoard(10);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      checkers_board->play(i, j, 0);
    }
  }

  checkers_board->play(4, 4, 2);
  checkers_board->play(2, 4, 2);
  checkers_board->play(2, 6, 2);
  checkers_board->play(5, 3, 1);
  checkers_board->print();

  std::vector<CheckersSequence*> sequences = checkers_board->get_sequences(5, 3);

  std::cout << "found " << sequences.size() << std::endl;

  for (auto sequence : sequences) {
    const std::vector<CheckersMove*>& moves = sequence->get_moves();
    std::cout << "size " << moves.size() << std::endl;

    for (auto move : moves) {
      move->print();
    }

    std::cout << "---------------" << std::endl;
  }

  checkers_board->print();
  delete checkers_board;
  return 0;
}
