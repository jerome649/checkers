#ifndef CHECKERS_NODE_H_
#define CHECKERS_NODE_H_

#include <string>
#include <vector>

class CheckersMove;

class CheckersNode {
public:
    CheckersNode(int i, int j);
    ~CheckersNode();
    int get_player();
    void set_player(int player);
    std::string get_letter();
    void set_neighbours(CheckersNode** n, int s);
    int get_i();
    int get_j();
    std::vector<CheckersMove*> eatable_moves();
    std::vector<CheckersMove*> vanilla_moves();
private:
  int id_i;
  int id_j;
  int player;
  int neighbours_size;
  CheckersNode** neighbours;
};

#endif
