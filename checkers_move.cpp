#include <iostream>
#include "checkers_move.hpp"

int CheckersMove::counter = 0;
int CheckersSequence::counter = 0;
int Tree::counter = 0;

CheckersMove::CheckersMove(CheckersNode* from, CheckersNode* to, CheckersNode* eat)
  : from(from), to(to), eat(eat) {
  CheckersMove::counter = CheckersMove::counter + 1;
}

CheckersMove::~CheckersMove() {
  CheckersMove::counter = CheckersMove::counter - 1;
}

CheckersMove* CheckersMove::copy() {
  return new CheckersMove(this->from, this->to, this->eat);
}

CheckersNode* CheckersMove::get_from() {
  return this->from;
}

CheckersNode* CheckersMove::get_to() {
  return this->to;
}

CheckersNode* CheckersMove::get_eat() {
  return this->eat;
}

bool CheckersMove::is_equal(CheckersMove* move) {
  return this->from == move->from && this->to == move->to && this->eat == move->eat;
}

void CheckersMove::print() {
  std::cout << from->get_i() << "/" << from->get_j() << " -> ";
  if (eat != NULL) {
    std::cout << eat->get_i() << "/" << eat->get_j() << " -> ";
  }
  std::cout << to->get_i() << "/" << to->get_j();
}

CheckersSequence::CheckersSequence() {
  CheckersSequence::counter = CheckersSequence::counter + 1;
}

CheckersSequence::~CheckersSequence() {
  CheckersSequence::counter = CheckersSequence::counter - 1;
  for (auto move : this->moves) {
    delete move;
  }
}

void CheckersSequence::add(CheckersMove* move) {
  this->moves.push_back(move);
}

CheckersSequence* CheckersSequence::copy() {
  CheckersSequence* copy = new CheckersSequence();
  for (auto move : this->moves) {
    copy->add(move->copy());
  }
  return copy;
}

bool CheckersSequence::is_equal(CheckersSequence* sequence) {
  if (sequence->moves.size() != this->moves.size()) {
    return false;
  }
  int i = 0;
  bool equal = true;
  int size = this->moves.size();
  while (i < size && equal) {
    equal = equal && this->moves[i]->is_equal(sequence->moves[i]);
    i = i + 1;
  }
  return equal;
}

std::vector<CheckersMove*> CheckersSequence::get_moves() {
  return this->moves;
}

void CheckersSequence::print() {
  for (auto move : moves) {
    move->print();
    std::cout << " ";
  }
  std::cout << std::endl;
}

Tree::Tree(Tree* parent, CheckersMove* move) {
  Tree::counter = Tree::counter + 1;
  this->visited = false;
  this->move = move;
  this->parent = parent;
}

Tree::~Tree() {
  Tree::counter = Tree::counter - 1;
  delete this->move;
  for (auto child : this->children) {
    delete child;
  }
}

bool Tree::is_leaf() {
  return this->children.size() == 0;
}

CheckersSequence* Tree::build() {
  std::vector<CheckersMove*> r;
  Tree* current = this;
  while (current->move != NULL) {
    r.push_back(current->move->copy());
    current = current->parent;
  }
  CheckersSequence* sequence = new CheckersSequence();
  for (int i = 0; i < r.size(); i++) {
    sequence->add(r[r.size() - i - 1]);
  }
  return sequence;
}

bool Tree::is_visited() {
  return this->visited;
}

void Tree::set_visited(){
  this->visited = true;
}

CheckersMove* Tree::get_move() {
  return this->move;
}

Tree* Tree::get_parent() {
  return this->parent;
}

void Tree::set_parent(Tree* parent){
  this->parent = parent;
}

void Tree::add_child(Tree* child) {
  this->children.push_back(child);
}

std::vector<Tree*> Tree::get_children() {
  return this->children;
}
