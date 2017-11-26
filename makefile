bin/main.app: obj/checkers_board.o obj/checkers_node.o obj/checkers_move.o obj/checkers_min_max.o src/main.cpp
	g++ -std=c++11 -Wall src/main.cpp obj/checkers_board.o obj/checkers_node.o obj/checkers_move.o obj/checkers_min_max.o -o bin/main.app

obj/checkers_board.o: src/checkers_board.cpp src/checkers_board.hpp src/checkers_move.hpp
	g++ -std=c++11 -Wall -c src/checkers_board.cpp -o obj/checkers_board.o

obj/checkers_node.o: src/checkers_node.cpp src/checkers_node.hpp src/checkers_move.hpp
	g++ -std=c++11 -Wall -c src/checkers_node.cpp -o obj/checkers_node.o

obj/checkers_move.o: src/checkers_move.cpp src/checkers_move.hpp src/checkers_node.hpp
	g++ -std=c++11 -Wall -c src/checkers_move.cpp -o obj/checkers_move.o

obj/checkers_min_max.o: src/checkers_min_max.cpp src/checkers_min_max.hpp src/checkers_move.hpp src/checkers_board.hpp
	g++ -std=c++11 -Wall -c src/checkers_min_max.cpp -o obj/checkers_min_max.o

tests: bin/test.app
	./bin/test.app

bin/test.app: tests/main_test.cpp tests/test_factorial.cpp tests/test_vector.cpp
	g++ -std=c++11 -Wall tests/main_test.cpp tests/test_factorial.cpp tests/test_vector.cpp -o bin/test.app

clean: cleans.o cleans.app

cleans.o:
	rm obj/*.o

cleans.app:
	rm bin/*.app
