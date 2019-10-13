#include <unistd.h>

#include "sokoban.hpp"

Sokoban::Sokoban(std::string t_board, size_t t_cols, size_t t_rows)
{
    m_board = t_board;
    m_rows  = t_rows;
    m_cols  = t_cols;
    m_agent = t_board.find_first_of('M');
}

void Sokoban::print()
{
    for (unsigned int i = 0; i < (m_cols*m_rows); i++)
    {
        if (i!=0 && !(i%m_cols))
            std::cout << std::endl;
        std::cout << m_board[i];
    }
    std::cout << std::endl; 
}

void Sokoban::move(int t_dx, int t_dy)
{
    int agent_m1 = m_agent + (t_dx + t_dy*m_cols);
    int agent_m2 = m_agent + (2*t_dx + 2*t_dy*m_cols);
     
    if(isBox(m_board[agent_m1]) && isFree(m_board[agent_m2]))
        moveCell(m_board[agent_m1], m_board[agent_m2]);
    
    if(isFree(m_board[agent_m1]))
    {
        moveCell(m_board[m_agent], m_board[agent_m1]);
        m_agent = agent_m1;
    }
}

void Sokoban::playback(std::string t_solution)
{ 
    system("clear");
    print();
    for(unsigned int i = 0; i < t_solution.length(); i++)
    {   
        usleep(150000);
        switch(t_solution[i])
        {
        case 'u': case 'U':
            move(0,-1);
            break;
        case 'd': case 'D':
            move(0,1);
            break;
        case 'l': case 'L':
            move(-1,0);
            break;
        case 'r': case 'R':
            move(1,0);
            break;
        } 
        system("clear"); // Scuffed
        print();
    }
}

void Sokoban::moveCell(char &t_src, char &t_dst)
{
    if(isGoal(t_dst))
    {   
        if(isBox(t_src))
            t_dst = 'j';
        else
            t_dst = 'm';
    }
    else
    {
        if(isBox(t_src))
            t_dst = 'J';
        else
            t_dst = 'M';
    }

    if(isGoal(t_src))
        t_src = 'G';
    else
        t_src = '.';
}

bool Sokoban::isGoal(char t_cell)
{
    return (t_cell == 'm' || 
            t_cell == 'j' || 
            t_cell == 'G');
}

bool Sokoban::isBox(char t_cell)
{
    return (t_cell == 'J' || t_cell == 'j');
}

bool Sokoban::isWall(char t_cell)
{
    return (t_cell == '#');
}

bool Sokoban::isFree(char t_cell)
{
    return (t_cell == '.' || t_cell == 'G');
}