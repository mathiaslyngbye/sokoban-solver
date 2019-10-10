#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <iostream>
#include <string>

class Sokoban
{
public:
    Sokoban(std::string t_board, int t_cols, int t_rows);
    void print();
    void move(int t_dx, int t_dy);
    void playback(std::string t_solution);
private:
    void moveCell(char &t_src, char &t_dst);
    bool isBox(char t_cell);
    bool isGoal(char t_cell);
    bool isWall(char t_cell);
    bool isFree(char t_cell);
    std::string m_board;
    int m_rows;
    int m_cols;
    int m_agent;
};

#endif
