#include "checkers_node.hpp"

class CheckersBoard {
public:
  CheckersBoard(int size);
  ~CheckersBoard();
  void print();
private:
  bool in_board(int i, int j);
  void fill_neighbours();
  int size;
  CheckersNode*** nodes;
};
