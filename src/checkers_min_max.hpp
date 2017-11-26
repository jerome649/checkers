#ifndef CHECKERS_MIN_MAX_H_
#define CHECKERS_MIN_MAX_H_

#include "checkers_move.hpp"
#include "checkers_board.hpp"
#include <vector>

class MinMaxNode {
public:
  MinMaxNode(int max_depth, int depth, CheckersBoard* board, int player, bool is_min, CheckersSequence* move);
  ~MinMaxNode();
  int get_depth();
  const std::vector<MinMaxNode*>& get_children();
  int compute_value();
  MinMaxNode* get_best_child();
  CheckersSequence* get_move();
private:
  CheckersSequence* move;
  int depth;
  int player;
  int max_depth;
  bool is_min;
  CheckersBoard* board;
  std::vector<MinMaxNode*> children;
  MinMaxNode* best_child;
};

class CheckersMinMax {
public:
  CheckersMinMax(int max_depth, CheckersBoard* board);
  ~CheckersMinMax();
  CheckersSequence* min_max_move(int player);
private:
  int max_depth;
  CheckersBoard* board;
};

#endif
