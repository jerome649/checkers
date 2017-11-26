#ifndef CHECKERS_BOARD_H_
#define CHECKERS_BOARD_H_

#include <vector>
#include "checkers_node.hpp"
#include "checkers_move.hpp"

class CheckersBoard {
public:
  CheckersBoard(int size);
  ~CheckersBoard();
  void print();
  std::vector<CheckersSequence*> get_moves(int player);
  int get_score(int player);
  void apply(CheckersMove* move);
  void de_apply(CheckersMove* move);
  void apply(CheckersSequence* move);
  void de_apply(CheckersSequence* move);
  void play(int i, int j, int player);
  CheckersNode* get_node(int i, int j);
private:
  std::vector<CheckersSequence*> get_sequences(int i, int j, bool& eat);
  bool in_board(int i, int j);
  void fill_neighbours();
  int size;
  CheckersNode*** nodes;
};

#endif
