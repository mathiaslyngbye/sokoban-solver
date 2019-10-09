#include "sokoban.hpp"

Sokoban::Sokoban(std::string t_board, int t_rows, int t_cols)
{
    m_board = t_board;
    m_rows  = t_rows;
    m_cols  = t_cols;
}

void Sokoban::print()
{
    std::cout << "Rows: " << m_rows << std::endl;
    std::cout << "Cols: " << m_cols << std::endl;
}

