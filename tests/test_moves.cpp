#include "../third_parties/catch2/catch.hpp"
#include "../src/checkers_board.hpp"

TEST_CASE("check available moves", "[moves]") {

  int size = 10;
  CheckersBoard checkers_board(size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      checkers_board.play(i, j, 0);
    }
  }

  SECTION("player 1 cannot eat") {
      checkers_board.play(1, 2, 1);
      checkers_board.play(6, 7, 1);
      std::vector<CheckersSequence*> sequences = checkers_board.get_moves(1);

      REQUIRE(sequences.size() == 4);

      std::vector<CheckersMove*> moves0 = sequences[0]->get_moves();
      std::vector<CheckersMove*> moves1 = sequences[1]->get_moves();
      std::vector<CheckersMove*> moves2 = sequences[2]->get_moves();
      std::vector<CheckersMove*> moves3 = sequences[3]->get_moves();

      REQUIRE(moves0.size() == 1);
      REQUIRE(moves0[0]->get_eat() == NULL);
      REQUIRE(moves0[0]->get_from()->get_i() == 1);
      REQUIRE(moves0[0]->get_from()->get_j() == 2);
      REQUIRE(moves0[0]->get_to()->get_i() == 0);
      REQUIRE(moves0[0]->get_to()->get_j() == 1);

      REQUIRE(moves1.size() == 1);
      REQUIRE(moves1[0]->get_eat() == NULL);
      REQUIRE(moves1[0]->get_from()->get_i() == 1);
      REQUIRE(moves1[0]->get_from()->get_j() == 2);
      REQUIRE(moves1[0]->get_to()->get_i() == 0);
      REQUIRE(moves1[0]->get_to()->get_j() == 3);

      REQUIRE(moves2.size() == 1);
      REQUIRE(moves2[0]->get_eat() == NULL);
      REQUIRE(moves2[0]->get_from()->get_i() == 6);
      REQUIRE(moves2[0]->get_from()->get_j() == 7);
      REQUIRE(moves2[0]->get_to()->get_i() == 5);
      REQUIRE(moves2[0]->get_to()->get_j() == 6);

      REQUIRE(moves3.size() == 1);
      REQUIRE(moves3[0]->get_eat() == NULL);
      REQUIRE(moves3[0]->get_from()->get_i() == 6);
      REQUIRE(moves3[0]->get_from()->get_j() == 7);
      REQUIRE(moves3[0]->get_to()->get_i() == 5);
      REQUIRE(moves3[0]->get_to()->get_j() == 8);

      for (auto move : sequences) {
        delete move;
      }
  }

  SECTION("player 2 cannot eat") {
    checkers_board.play(1, 2, 0);
    checkers_board.play(6, 7, 2);
    std::vector<CheckersSequence*> sequences = checkers_board.get_moves(2);

    REQUIRE(sequences.size() == 2);

    std::vector<CheckersMove*> moves0 = sequences[0]->get_moves();
    std::vector<CheckersMove*> moves1 = sequences[1]->get_moves();

    REQUIRE(moves0.size() == 1);
    REQUIRE(moves0[0]->get_eat() == NULL);
    REQUIRE(moves0[0]->get_from()->get_i() == 6);
    REQUIRE(moves0[0]->get_from()->get_j() == 7);
    REQUIRE(moves0[0]->get_to()->get_i() == 7);
    REQUIRE(moves0[0]->get_to()->get_j() == 6);

    REQUIRE(moves1.size() == 1);
    REQUIRE(moves1[0]->get_eat() == NULL);
    REQUIRE(moves1[0]->get_from()->get_i() == 6);
    REQUIRE(moves1[0]->get_from()->get_j() == 7);
    REQUIRE(moves1[0]->get_to()->get_i() == 7);
    REQUIRE(moves1[0]->get_to()->get_j() == 8);
  }

  SECTION("player 2 can move once") {
    checkers_board.play(6, 7, 2);
    checkers_board.play(7, 8, 1);
    checkers_board.play(8, 9, 1);
    std::vector<CheckersSequence*> sequences = checkers_board.get_moves(2);

    REQUIRE(sequences.size() == 1);

    std::vector<CheckersMove*> moves0 = sequences[0]->get_moves();

    REQUIRE(moves0.size() == 1);
    REQUIRE(moves0[0]->get_eat() == NULL);
    REQUIRE(moves0[0]->get_from()->get_i() == 6);
    REQUIRE(moves0[0]->get_from()->get_j() == 7);
    REQUIRE(moves0[0]->get_to()->get_i() == 7);
    REQUIRE(moves0[0]->get_to()->get_j() == 6);
  }

  SECTION("player 2 can eat") {
    checkers_board.play(6, 7, 2);
    checkers_board.play(7, 8, 1);
    checkers_board.play(8, 9, 0);
    std::vector<CheckersSequence*> sequences = checkers_board.get_moves(2);

    REQUIRE(sequences.size() == 1);

    std::vector<CheckersMove*> moves0 = sequences[0]->get_moves();

    REQUIRE(moves0.size() == 1);
    REQUIRE(moves0[0]->get_eat()->get_i() == 7);
    REQUIRE(moves0[0]->get_eat()->get_j() == 8);
    REQUIRE(moves0[0]->get_from()->get_i() == 6);
    REQUIRE(moves0[0]->get_from()->get_j() == 7);
    REQUIRE(moves0[0]->get_to()->get_i() == 8);
    REQUIRE(moves0[0]->get_to()->get_j() == 9);
  }


}
