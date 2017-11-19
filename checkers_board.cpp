#include <iostream>
#include <vector>
#include "checkers_board.hpp"

CheckersBoard::CheckersBoard(int size) : size(size), nodes(new CheckersNode**[size])  {
  for (int i = 0; i < this->size; i++) {
    this->nodes[i] = new CheckersNode*[size];
    for (int j = 0; j < this->size; j++) {
      this->nodes[i][j] = new CheckersNode(i,  j);
    }
  }

  int pieces_per_line = this->size / 2;
  int lines = pieces_per_line - 1;

  for (int i = 0; i < lines; i++) {
    int offset_1 = i % 2;
    int offset_2 = (offset_1 == 0) ? 1 : 0;
    for (int j = 0; j < pieces_per_line; j++) {
      this->nodes[i][offset_2 + 2 * j]->set_player(2);
      this->nodes[this->size - 1 - i][offset_1 + 2 * j]->set_player(1);
    }
  }
  this->fill_neighbours();
}

CheckersBoard::~CheckersBoard() {
  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      delete this->nodes[i][j];
    }
    delete [] this->nodes[i];
  }
  delete [] this->nodes;
}

void CheckersBoard::fill_neighbours() {
  int moves_i[4] = {-1, -1, +1, +1};
  int moves_j[4] = {-1, +1, -1, +1};

  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      std::vector<CheckersNode*> v;
      int ni, nj;

      for (int l = 0; l < 4; l++) {
        ni = i + moves_i[l];
        nj = j + moves_j[l];
        if (this->in_board(ni, nj)) {
          v.push_back(this->nodes[ni][nj]);
        }
      }

      int s = v.size();
      CheckersNode** res = new CheckersNode*[s];
      for (int k = 0; k < s; k++) {
        res[k] = v[k];
      }
      this->nodes[i][j]->set_neighbours(res, s);
    }
  }
}

bool CheckersBoard::in_board(int i, int j) {
  return 0 <= i && i < this->size && 0 <= j && j < this->size;
}

void CheckersBoard::print() {
  std::cout << "  ";
  for (int i = 0; i < this->size; i++) {
    std::cout << " " << i << "  ";
  }
  std::cout << std::endl << "  ";
  for (int i = 0; i < this->size; i++) {
    std::cout << "----";
  }
  std::cout << std::endl;

  for (int i = 0; i < this->size; i++) {
    std::cout << i << "| ";
    for (int j = 0; j < this->size; j++) {
      std::cout << this->nodes[i][j]->get_letter() << " | ";
    }
    std::cout << std::endl << "  ";
    for (int j = 0; j < this->size; j++) {
      std::cout << "----";
    }
    std::cout << std::endl;
  }
}
