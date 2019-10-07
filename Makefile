all: sokoban-solver

sokoban-solver: main.cpp
	g++ -std=c++17 -Wall -Wextra -Wpedantic -pedantic -o ./build/sokoban-solver main.cpp

clean:
	rm sokoban-solver

.PHONY: all clean
