#include <iostream>
#include <vector>
#include "checkers_board.hpp"
#include "checkers_node.hpp"
#include "checkers_move.hpp"
#include "checkers_min_max.hpp"

void free_moves(std::vector<CheckersSequence*>& moves) {
  for (auto move : moves) {
    delete move;
  }
}

int main() {
  std::cout << "Checkers" << std::endl;
  CheckersBoard* checkers_board = new CheckersBoard(10);
  checkers_board->print();

  int player = 2;
  for (int i = 0; i < 20; i++) {
    player = (player == 2) ? 1 : 2;
    std::cout << "Player " << player << " to play" << std::endl;
    auto moves = checkers_board->get_moves(player);

    if (moves.size() > 0) {
      for (int i = 0; i < moves.size(); i++) {
        std::cout << i << ")";
        moves[i]->print();
      }
    }

    int choice;
    std::cin >> choice;
    checkers_board->apply(moves[choice]);
    checkers_board->print();
    free_moves(moves);
    std::cout << "CheckersMove::counter=" << CheckersMove::counter << std::endl;
    std::cout << "CheckersSequence::counter=" << CheckersSequence::counter << std::endl;
    std::cout << "Tree::counter=" << Tree::counter << std::endl;
  }

  delete checkers_board;
  return 0;
}
