#include <iostream>
#include <vector>
#include <stack>
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

CheckersNode* CheckersBoard::get_node(int i, int j) {
  return this->nodes[i][j];
}

void CheckersBoard::play(int i, int j, int player) {
  this->nodes[i][j]->set_player(player);
}

bool CheckersBoard::in_board(int i, int j) {
  return 0 <= i && i < this->size && 0 <= j && j < this->size;
}

std::vector<CheckersSequence*> CheckersBoard::get_moves(int player) {
  std::vector<CheckersSequence*> res_eat;
  std::vector<CheckersSequence*> res_no_eat;

  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      if (this->nodes[i][j]->get_player() == player) {
        bool eat;
        auto moves = this->get_sequences(i, j, eat);
        for (auto move : moves) {
          if (eat) {
            res_eat.push_back(move);
          } else {
            res_no_eat.push_back(move);
          }
        }
      }
    }
  }

  if (res_eat.size() > 0) {
    for (auto move : res_no_eat) {
      delete move;
    }
    return res_eat;
  } else {
    for (auto move : res_eat) {
      delete move;
    }
    return res_no_eat;
  }
}

std::vector<CheckersSequence*> CheckersBoard::get_sequences(int i, int j, bool& eat) {
  std::vector<CheckersSequence*> res;

  std::vector<CheckersMove*> moves = this->nodes[i][j]->eatable_moves();

  if (moves.size() == 0) {
    auto vanillas = this->nodes[i][j]->vanilla_moves();

    for (auto vanilla : vanillas) {
      auto sequence = new CheckersSequence();
      sequence->add(vanilla);
      res.push_back(sequence);
    }
    eat = false;
    return res;
  }
  Tree* root = new Tree(NULL, NULL);
  Tree* tree = root;
  for (auto move : moves) {
    tree->add_child(new Tree(tree, move));
  }
  while (tree != NULL) {
    tree->set_visited();
    if (tree->is_leaf()) {
      res.push_back(tree->build());
      this->de_apply(tree->get_move());
      tree = tree->get_parent();
    } else {
      Tree* child = NULL;
      const std::vector<Tree*>& children = tree->get_children();
      int i = 0;
      while (child == NULL && i < children.size()) {
        if (!children[i]->is_visited()) {
          child = children[i];
        }
        i = i + 1;
      }
      if (child != NULL) {
        this->apply(child->get_move());
        CheckersNode* node = child->get_move()->get_to();
        std::vector<CheckersMove*> c_moves = this->nodes[node->get_i()][node->get_j()]->eatable_moves();
        for (auto move : c_moves) {
          child->add_child(new Tree(child, move));
        }
        tree = child;
      } else {
        if (tree->get_move() != NULL) {
          this->de_apply(tree->get_move());
        }
        tree = tree->get_parent();
      }
    }
  }

  delete root;
  eat = true;
  return res;
}

int CheckersBoard::get_score(int player) {
  int p1 = 0;
  int p2 = 0;

  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      if (this->nodes[i][j]->get_player() == 1) {
        p1 = p1 + 1;
      } else if (this->nodes[i][j]->get_player() == 2) {
        p2 = p2 + 1;
      }
    }
  }

  if (player == 1) {
    return p1 - p2;
  } else {
    return p2 - p1;
  }

}

void CheckersBoard::apply(CheckersMove* move) {
  if (move->get_eat() != NULL) {
    this->nodes[move->get_eat()->get_i()][move->get_eat()->get_j()]
      ->set_player(0);
  }

  this->nodes[move->get_to()->get_i()][move->get_to()->get_j()]
    ->set_player(move->get_from()->get_player());

  this->nodes[move->get_from()->get_i()][move->get_from()->get_j()]
    ->set_player(0);
}

void CheckersBoard::de_apply(CheckersMove* move) {
  int player = this->nodes[move->get_to()->get_i()][move->get_to()->get_j()]->get_player();
  int opponent = (player == 2) ? 1 : 2;

  if (move->get_eat() != NULL) {
    this->nodes[move->get_eat()->get_i()][move->get_eat()->get_j()]
      ->set_player(opponent);
  }

  this->nodes[move->get_from()->get_i()][move->get_from()->get_j()]
    ->set_player(player);

  this->nodes[move->get_to()->get_i()][move->get_to()->get_j()]
    ->set_player(0);
}

void CheckersBoard::apply(CheckersSequence* moves) {
  for (auto move : moves->get_moves()) {
    this->apply(move);
  }
}

void CheckersBoard::de_apply(CheckersSequence* moves) {
  std::vector<CheckersMove*> sequences = moves->get_moves();
  for (int i = 0; i < sequences.size(); i++) {
    this->de_apply(sequences[sequences.size() - 1 - i]);
  }
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
