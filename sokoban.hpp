#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <iostream>
#include <string>

class Sokoban
{
public:
    Sokoban(std::string t_board, int t_rows, int t_cols);
    void print();
    std::string m_board;
    int m_rows;
    int m_cols;
private:
};
#endif
