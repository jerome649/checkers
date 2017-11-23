#ifndef CHECKERS_MOVE_H_
#define CHECKERS_MOVE_H_

#include "checkers_node.hpp"


class CheckersMove {
public:
  CheckersMove(CheckersNode* from, CheckersNode* to, CheckersNode* eat);
  ~CheckersMove();
  CheckersNode* get_from();
  CheckersNode* get_to();
  CheckersNode* get_eat();
  CheckersMove* copy();
  void print();
private:
  CheckersNode* from;
  CheckersNode* to;
  CheckersNode* eat;
};

class CheckersSequence {
public:
  CheckersSequence();
  ~CheckersSequence();
  void add(CheckersMove* move);
  std::vector<CheckersMove*> get_moves();
  void print();
private:
  std::vector<CheckersMove*> moves;
};

class Tree {
public:
  Tree(Tree* parent, CheckersMove* move);
  ~Tree();
  bool is_leaf();
  bool is_visited();
  void set_visited();
  CheckersMove* get_move();
  Tree* get_parent();
  void set_parent(Tree* parent);
  void add_child(Tree* child);
  CheckersSequence* build();
  std::vector<Tree*> get_children();
private:
  bool visited;
  CheckersMove* move;
  Tree* parent;
  std::vector<Tree*> children;
};

#endif
