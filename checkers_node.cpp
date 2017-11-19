#include "checkers_node.hpp"

CheckersNode::CheckersNode(int i, int j) : id_i(i), id_j(j), player(0) {

}

CheckersNode::~CheckersNode() {
  delete [] this->neighbours;
}

int CheckersNode::get_player() {
  return this->player;
}

void CheckersNode::set_player(int player) {
  this->player = player;
}

int CheckersNode::get_i() {
  return this->id_i;
}

int CheckersNode::get_j() {
  return this->id_j;
}

std::string CheckersNode::get_letter() {
  if (this->player == 1) {
    return "X";
  } else if (this->player == 2) {
    return "O";
  } else {
    return " ";
  }
}

void CheckersNode::set_neighbours(CheckersNode** n, int s) {
  this->neighbours = n;
  this->neighbours_size = s;
}
