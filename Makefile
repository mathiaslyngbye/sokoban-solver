all: sokoban-solver

sokoban-solver: main.cpp
	mkdir -p build
	g++ -std=c++17 -Wall -Wextra -Wpedantic -pedantic -o ./build/sokoban-solver main.cpp

clean:
	rm ./build/sokoban-solver

.PHONY: all clean
