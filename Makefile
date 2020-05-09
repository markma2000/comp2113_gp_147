FLAGS = -pedantic-errors -std=c++11

Board.o: Board.cpp Board.h
	g++ $(FLAGS) -c $<

Board_main.o: Board_main.cpp Board.cpp Board.h
	g++ $(FLAGS) -c $<

Board_main: Board.o Board_main.o
	g++ $(FLAGS) $^ -o $@


clean:
	rm -f Board.o Board_main.o Board_main Board.tgz

.PHONY: clean tar


