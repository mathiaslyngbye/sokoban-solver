CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

all: sokoban-solver

sokoban-solver: main.o sokoban.o
	mkdir -p build
	$(CXX) $(CXXFLAGS) main.o sokoban.o -o ./build/sokoban-solver

main.o: main.cpp
	$(CXX) -c main.cpp

sokoban.o: sokoban.cpp sokoban.hpp
	$(CXX) -c sokoban.cpp

clean:
	rm *.o
	rm ./build/sokoban-solver

.PHONY: all sokoban-solver clean
