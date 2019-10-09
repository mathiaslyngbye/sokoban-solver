#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <iostream>
#include <string>

class Sokoban
{
public:
    Sokoban(std::string t_board, int t_rows, int t_cols);
    void print();
    void move(int t_dx, int t_dy);
private:
    bool isBox(char t_tile);
    bool isGoal(char t_tile);
    bool isWall(char t_tile);
    std::string m_board;
    int m_rows;
    int m_cols;
    int m_agent;
};

#endif
