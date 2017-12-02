FLAGS= -std=c++11 -Wall
OBJS=obj/checkers_board.o obj/checkers_node.o obj/checkers_move.o obj/checkers_min_max.o

bin/main.app: ${OBJS} src/main.cpp
	g++ ${FLAGS} ${OBJS} src/main.cpp  -o bin/main.app

obj/checkers_board.o: src/checkers_board.cpp src/checkers_board.hpp src/checkers_move.hpp
	g++ ${FLAGS} -c src/checkers_board.cpp -o obj/checkers_board.o

obj/checkers_node.o: src/checkers_node.cpp src/checkers_node.hpp src/checkers_move.hpp
	g++ ${FLAGS} -c src/checkers_node.cpp -o obj/checkers_node.o

obj/checkers_move.o: src/checkers_move.cpp src/checkers_move.hpp src/checkers_node.hpp
	g++ ${FLAGS} -c src/checkers_move.cpp -o obj/checkers_move.o

obj/checkers_min_max.o: src/checkers_min_max.cpp src/checkers_min_max.hpp src/checkers_move.hpp src/checkers_board.hpp
	g++ ${FLAGS} -c src/checkers_min_max.cpp -o obj/checkers_min_max.o

tests: bin/test.app
	./bin/test.app

bin/test.app: tests/main_test.cpp tests/test_moves.cpp ${OBJS}
	g++ ${FLAGS} ${OBJS} tests/main_test.cpp tests/test_moves.cpp  -o bin/test.app

clean: cleans.o cleans.app

cleans.o:
	rm obj/*.o

cleans.app:
	rm bin/*.app
