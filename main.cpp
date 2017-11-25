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

  CheckersMinMax* min_max = new CheckersMinMax(6, checkers_board);

  int player = 2;
  for (int i = 0; i < 40; i++) {
    player = (player == 2) ? 1 : 2;
    std::cout << "Player " << player << " to play" << std::endl;
    auto moves = checkers_board->get_moves(player);

    if (moves.size() > 0) {
      for (int i = 0; i < moves.size(); i++) {
        std::cout << i << ")";
        moves[i]->print();
      }
    }

    if (player == 2) {
      CheckersSequence* seq = min_max->min_max_move(player);
      std::cout << "min max advise : ";
      seq->print();
      std::cout << std::endl;
      int choice_auto = 0;
      bool found = false;
      while (choice_auto < moves.size() && !found) {
        if (moves[choice_auto]->is_equal(seq)) {
          found = true;
        } else {
          choice_auto = choice_auto + 1;
        }
      }
      std::cout << "min max plays " << choice_auto << std::endl;
      checkers_board->apply(moves[choice_auto]);
      delete seq;
    } else {
      int choice;
      std::cin >> choice;
      checkers_board->apply(moves[choice]);
    }

    checkers_board->print();
    free_moves(moves);
    std::cout << "CheckersMove::counter=" << CheckersMove::counter << std::endl;
    std::cout << "CheckersSequence::counter=" << CheckersSequence::counter << std::endl;
    std::cout << "Tree::counter=" << Tree::counter << std::endl;
  }

  delete checkers_board;
  return 0;
}
