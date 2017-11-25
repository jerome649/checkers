#include "checkers_min_max.hpp"

MinMaxNode::MinMaxNode(int max_depth, int depth, CheckersBoard* board, int player, bool is_min, CheckersSequence* move) {
  this->max_depth = max_depth;
  this->board = board;
  this->player = player;
  this->is_min = is_min;
  this->depth = depth;
  this->move = move;
}

MinMaxNode::~MinMaxNode() {
  delete this->move;
  for (auto child : this->children) {
    delete child;
  }
}

int MinMaxNode::get_depth() {
  return this->depth;
}

MinMaxNode* MinMaxNode::get_best_child() {
  return this->best_child;
}

CheckersSequence* MinMaxNode::get_move() {
  return this->move;
}

int MinMaxNode::compute_value() {
  if (this->max_depth == this->depth) {
    return this->board->get_score(this->player);
  } else {
    std::vector<CheckersSequence*> moves = this->board->get_moves(this->player);
    int opponent = (player == 2) ? 1 : 2;
    int min_max = is_min ? 9999999 : -9999999;
    for (auto move : moves) {
      auto node = new MinMaxNode(max_depth, depth + 1, board, opponent, !is_min, move);
      this->board->apply(move);
      int child_value = node->compute_value();
      if (is_min) {
        if (child_value < min_max) {
          min_max = child_value;
          this->best_child = node;
        }
      } else {
        if (child_value > min_max) {
          min_max = child_value;
          this->best_child = node;
        }
      }
      this->board->de_apply(move);
      children.push_back(node);
    }
    return min_max;
  }
}

const std::vector<MinMaxNode*>& MinMaxNode::get_children() {
  return this->children;
}

CheckersMinMax::CheckersMinMax(int max_depth, CheckersBoard* board)
  : max_depth(max_depth), board(board) {

}

CheckersMinMax::~CheckersMinMax() {

}

CheckersSequence* CheckersMinMax::min_max_move(int player) {
  auto root = new MinMaxNode(max_depth, 0, board, player, false, NULL);
  root->compute_value();
  CheckersSequence* res = root->get_best_child()->get_move()->copy();
  delete root;
  return res;
}
