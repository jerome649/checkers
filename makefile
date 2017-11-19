bin/main.app: obj/checkers_board.o obj/checkers_node.o main.cpp
	g++ -std=c++11 -Wall main.cpp obj/checkers_board.o obj/checkers_node.o -o bin/main.app

obj/checkers_board.o: checkers_board.cpp checkers_board.hpp checkers_board.hpp
	g++ -std=c++11 -Wall -c checkers_board.cpp -o obj/checkers_board.o

obj/checkers_node.o: checkers_node.cpp checkers_node.hpp
	g++ -std=c++11 -Wall -c checkers_node.cpp -o obj/checkers_node.o

clean: cleans.o cleans.app

cleans.o:
	rm obj/*.o

cleans.app:
	rm bin/*.app
