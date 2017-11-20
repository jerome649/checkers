bin/main.app: obj/checkers_board.o obj/checkers_node.o obj/checkers_move.o main.cpp
	g++ -std=c++11 -Wall main.cpp obj/checkers_board.o obj/checkers_node.o obj/checkers_move.o -o bin/main.app

obj/checkers_board.o: checkers_board.cpp checkers_board.hpp checkers_move.hpp
	g++ -std=c++11 -Wall -c checkers_board.cpp -o obj/checkers_board.o

obj/checkers_node.o: checkers_node.cpp checkers_node.hpp checkers_move.hpp
	g++ -std=c++11 -Wall -c checkers_node.cpp -o obj/checkers_node.o

obj/checkers_move.o: checkers_move.cpp checkers_move.hpp checkers_node.hpp
	g++ -std=c++11 -Wall -c checkers_move.cpp -o obj/checkers_move.o

clean: cleans.o cleans.app

cleans.o:
	rm obj/*.o

cleans.app:
	rm bin/*.app
