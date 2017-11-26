#include <iostream>
#include "checkers_node.hpp"
#include "checkers_move.hpp"

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

std::vector<CheckersMove*> CheckersNode::eatable_moves() {
  std::vector<CheckersMove*> v;

  int opponent = (this->player == 2) ? 1 : 2;
  for (int i = 0; i < this->neighbours_size; i++) {
    CheckersNode* neighbour = this->neighbours[i];
    if (neighbour->player == opponent) {
      for (int j = 0; j < neighbour->neighbours_size; j++) {
        CheckersNode* opp_neighbour = neighbour->neighbours[j];
        int offset_i_1 = neighbour->get_i() - this->get_i();
        int offset_i_2 = opp_neighbour->get_i() - neighbour->get_i();
        int offset_j_1 = neighbour->get_j() - this->get_j();
        int offset_j_2 = opp_neighbour->get_j() - neighbour->get_j();
        if (offset_i_1 == offset_i_2 && offset_j_1 == offset_j_2 && opp_neighbour->player == 0) {
          v.push_back(new CheckersMove(this, opp_neighbour, neighbour));
        }
      }
    }
  }

  return v;
}

std::vector<CheckersMove*> CheckersNode::vanilla_moves() {
  std::vector<CheckersMove*> v;

  for (int i = 0; i < this->neighbours_size; i++) {
    CheckersNode* neighbour = this->neighbours[i];
    if (neighbour->player == 0) {
      int offset_i = neighbour->get_i() - this->get_i();
      if (offset_i < 0 && this->player == 1) {
        v.push_back(new CheckersMove(this, neighbour, NULL));
      }
      if (offset_i > 0 && this->player == 2) {
        v.push_back(new CheckersMove(this, neighbour, NULL));
      }
    }
  }
  return v;
}
