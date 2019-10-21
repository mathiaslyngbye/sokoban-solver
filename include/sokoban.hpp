#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <iostream>
#include <string>
#include <vector>

class Sokoban
{
public:
    Sokoban(std::string t_board, size_t t_cols, size_t t_rows);
    void print();
    bool move(int t_dx, int t_dy);
    void playback(std::string t_solution);
    bool isWin();
private:
    void moveCell(char &t_src, char &t_dst);
    void findGoals(std::vector<size_t> &t_goals, std::string t_board);
    bool isBox(char t_cell);
    bool isGoal(char t_cell);
    bool isWall(char t_cell);
    bool isFree(char t_cell);
    std::string m_board;
    size_t m_rows;
    size_t m_cols;
    unsigned int m_agent;
    std::vector<size_t> m_goals;
};

#endif

