#include <unistd.h>
#include <array>
#include <queue>
#include <algorithm>
#include "sokoban.hpp"

Sokoban::Sokoban(std::string t_board, size_t t_cols, size_t t_rows) : 
m_board(t_board), m_rows(t_rows), m_cols(t_cols)
{
    m_agent = m_board.find_first_of("Mm");
    findGoals(m_goals, m_board);
    findCorners(m_corners, m_board);
    findEdges(m_edges, m_board);
}

void Sokoban::print()
{
    for (unsigned int i = 0; i < (m_cols*m_rows); i++)
    {
        if (i!=0 && !(i%m_cols))
            std::cout << '\n';
        std::cout << m_board[i];
    }
    std::cout << std::endl; 
}

bool Sokoban::move(int t_dx, int t_dy)
{
    int agent_m1 = m_agent + (t_dx + t_dy*m_cols);
    int agent_m2 = m_agent + (2*t_dx + 2*t_dy*m_cols);
     
    if(isBox(m_board[agent_m1]) && isFree(m_board[agent_m2]))
        moveCell(m_board[agent_m1], m_board[agent_m2]);
    
    if(isFree(m_board[agent_m1]))
    {
        moveCell(m_board[m_agent], m_board[agent_m1]);
        m_agent = agent_m1;
        return true;
    }
    else
        return false;
}

bool Sokoban::solve()
{
    // Define movements
    int dirs[4][2] = {
        { 0,-1},    // Up
        { 1, 0},    // Right
        { 0, 1},    // Down
        {-1, 0}     // Left
    };
    
    char dirs_c[4] = {'u','r','d','l'};

    // Create visited list
    std::vector<std::string> visited;
    
    // Create open queue
    std::queue<std::array<std::string, 2>> open;

    // Push start state to open queue
    std::array<std::string,2> tmp_state = {m_board, ""};
    open.push(tmp_state);

    // Insert start state in visited tree
    visited.push_back(m_board);
     
    size_t last_depth = 0;
    size_t curr_depth = 0;
    
    while(!open.empty())
    {
        std::string tmp_board = open.front()[0];
        std::string tmp_sol   = open.front()[1];
        size_t tmp_agent      = tmp_board.find_first_of("Mm");

        last_depth = curr_depth;
        curr_depth = tmp_sol.length();

        if(last_depth != curr_depth)
        {
            std::cout << "Depth:\t" << curr_depth << std::endl;
            std::cout << "Open:\t"  << open.size() << std::endl; 
            std::cout << "Closed:\t" << visited.size() << std::endl;
            std::cout << std::endl; 
        }

        
        for(size_t i = 0; i<4; i++)
        {
            m_board = tmp_board;
            m_agent = tmp_agent;

            move(dirs[i][0], dirs[i][1]);
            if (!(std::find(visited.begin(), visited.end(),m_board) 
                != visited.end()))
            {
                if(isWin())
                {
                    std::cout << std::endl << tmp_sol+dirs_c[i] << std::endl;
                    print();
                    return true;
                }
                if(!isStuck())
                {
                    std::array<std::string,2> tmp_state = {
                        m_board, tmp_sol+dirs_c[i] };
                    open.push(tmp_state);
                    visited.push_back(m_board);
                }
            }      
        }
        
        open.pop();
    }
    return false;
}

void Sokoban::play() 
{
    // Scuffed user input
    std::string tmp_board = m_board;
    int tmp_agent = m_agent;

    system("clear");
    while(1)
    {
        print();
        if(isWin())
        {
            std::cout << "You win!" << std::endl;
        }
        if(isStuck())
        {
            std::cout << "You are stuck!" << std::endl;
        }
        std::cout << "Input: ";
        char key;
        std::cin >> key;

        system("clear");
        switch(key)
        {
        case 'a':
            move(-1,0);
            break;
        case 's':
            move(0,1);
            break;
        case 'd':
            move(1,0);
            break;
        case 'w':
            move(0,-1);
            break;
        case 'r':
            m_board = tmp_board;
            m_agent = tmp_agent;
            break;
        default:
            return;
        }
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

bool Sokoban::isWin()
{
    for(size_t i = 0; i < m_goals.size(); i++)
    {
        if(m_board[m_goals[i]] != 'j')
            return false;
    }
    return true;
}

bool Sokoban::isStuck()
{
    for(size_t i = 0; i < m_corners.size(); i++)
    {
        if(isBox(m_board[m_corners[i]]))
            return true;
    }
    return false;
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

void Sokoban::findGoals(std::vector<size_t> &t_goals, std::string t_board)
{
    for(size_t i = 0; i<t_board.length();i++)
    {
        if(isGoal(t_board[i]))
            t_goals.push_back(i);
    }
}

void Sokoban::findCorners(std::vector<size_t> &t_corners, std::string t_board)
{
    for(size_t i = 0; i < t_board.length(); i++)
    {
        if( isFree(t_board[i]) && !isGoal(t_board[i]) &&
            (isWall(t_board[i-m_cols]) || isWall(t_board[i+m_cols])) &&
            (isWall(t_board[i-1]) || isWall(t_board[i+1]))) 
            t_corners.push_back(i);
    }
}

void Sokoban::findEdges(std::vector<size_t> &t_edges, std::string t_board)
{    
    for(size_t i = 0; i < m_rows; i++)
    {
        bool wallFlag0 = false;
        bool wallFlag1 = false;
        bool edgeFlag = false;

        for(size_t j = 0; j < m_cols; j++)
        {
            std::vector<int> tmp_edge;
            
            wallFlag0 = wallFlag1;
            wallFlag1 = !isFree(t_board[i*m_cols+j]);
            
            if(wallFlag0 && !wallFlag1)
                edgeFlag = true;
            else if (!wallFlag0 && !wallFlag1)
                edgeFlag = false;

            if(edgeFlag)
            {
                tmp_edge.push_back(i*m_cols+j);
                //std::cout << "I'm retarded" << std::endl;
            }
            else
                tmp_edge.clear();
        }
    }

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
    return (t_cell == 'X');
}

bool Sokoban::isFree(char t_cell)
{
    return (t_cell == '.' || t_cell == 'G');
}

bool Sokoban::isAgent(char t_cell)
{
    return (t_cell == 'M' || t_cell == 'm');
}
