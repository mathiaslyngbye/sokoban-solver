#include "sokoban.hpp"

Sokoban::Sokoban(std::string t_board, int t_rows, int t_cols)
{
    m_board = t_board;
    m_rows  = t_rows;
    m_cols  = t_cols;
    m_agent = t_board.find_first_of('M');
}

void Sokoban::print()
{
    for (unsigned int i = 0; i < (m_rows*m_cols); i++)
    {
        if (i!=0 && !(i%m_cols))
            std::cout << std::endl;
        std::cout << m_board[i];
    }
    std::cout << std::endl;
    std::cout << "Agent is at " << m_agent << std::endl;
}

void Sokoban::move(int t_dx, int t_dy)
{
    int agent_m1 = m_agent + (t_dx + t_dy*m_cols);
    int agent_m2 = m_agent + (2*t_dx + 2*t_dy*m_cols);
    
    if (isWall(m_board[agent_m1]) ||
       (isBox(m_board[agent_m1]) && isWall(m_board[agent_m2])) ||
       (isBox(m_board[agent_m1]) && isBox(m_board[agent_m2])))
    {
        ;
    }
    else
    {
        // This is disgusting
        if(isBox(m_board[agent_m1]))
        {
            if(isGoal(m_board[agent_m1]))
                m_board[agent_m1] = 'G';
            else
                m_board[agent_m1] = '.';

            if(isGoal(m_board[agent_m2]))
                m_board[agent_m2] = 'j';
            else
                m_board[agent_m2] = 'J';
        }
        
        if(isGoal(m_board[m_agent]))
            m_board[m_agent] = 'G';
        else
            m_board[m_agent] = '.';

        if(isGoal(m_board[agent_m1]))
            m_board[agent_m1] = 'm';
        else
            m_board[agent_m1] = 'M';
        
        m_agent = agent_m1;
    }
}

bool Sokoban::isGoal(char t_tile)
{
    return (t_tile == 'm' || 
            t_tile == 'j' || 
            t_tile == 'G');
}

bool Sokoban::isBox(char t_tile)
{
    return (t_tile == 'J' || t_tile == 'j');
}

bool Sokoban::isWall(char t_tile)
{
    return (t_tile == '#');
}
