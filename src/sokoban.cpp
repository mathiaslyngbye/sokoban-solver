#include <unistd.h>
#include <array>
#include <queue>
#include <algorithm>
#include <set>

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

bool Sokoban::move(int t_dx, int t_dy, bool &t_push)
{
    int agent_m1 = m_agent + (t_dx + t_dy*m_cols);
    int agent_m2 = m_agent + (2*t_dx + 2*t_dy*m_cols);
    
    t_push = false;

    if(isBox(m_board[agent_m1]) && isFree(m_board[agent_m2]))
    {
        moveCell(m_board[agent_m1], m_board[agent_m2]);
        t_push = true;
    }

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
    // Define movement arrays
    int dirs[4][2] = {
        { 0,-1},    // Up
        { 1, 0},    // Right
        { 0, 1},    // Down
        {-1, 0}     // Left
    }; 
    char dirs_c[4] = {'u','r','d','l'};

    // Create closed set
    std::set<std::string> closed;
    
    // Create open queue
    std::queue<std::array<std::string, 2>> open;

    // Push start state to open queue
    std::array<std::string,2> tmp_state = {m_board, ""};
    open.push(tmp_state);

    // Insert start state in visited tree
    closed.insert(m_board);

    // Initialize depth variables
    size_t last_depth = 0;
    size_t curr_depth = 0;
    
    while(!open.empty())
    {
        // Fetch data of node
        std::string tmp_board = open.front()[0];
        std::string tmp_sol   = open.front()[1];
        size_t tmp_agent      = tmp_board.find_first_of("Mm");

        // Print debug info on depth change
        last_depth = curr_depth;
        curr_depth = tmp_sol.length();
        if(last_depth != curr_depth)
        {
            std::cout << "Depth:\t" << curr_depth << std::endl;
            std::cout << "Open:\t"  << open.size() << std::endl; 
            std::cout << "Closed:\t" << closed.size() << std::endl;
            std::cout << std::endl; 
        }
        
        // Generate children
        for(size_t i = 0; i<4; i++)
        {
            // Reset board 
            m_board = tmp_board;
            m_agent = tmp_agent;
            
            // Perform move
            bool tmp_push = false;
            if(move(dirs[i][0], dirs[i][1], tmp_push))
            {
                if(closed.find(m_board) == closed.end())
                {
                    // Capitalize direction letter if pushing
                    char tmp_dir = dirs_c[i];
                    if(tmp_push)
                        tmp_dir -= 'a'-'A';

                    // Check if state is won
                    if(isWin())
                    {
                        std::cout << tmp_sol+tmp_dir << std::endl;
                        print();
                        return true;
                    }

                    // Check if state is stuck
                    if(!isStuck())
                    {
                        std::array<std::string,2> cur_state = {
                            m_board, tmp_sol+tmp_dir };
                        open.push(cur_state);
                        closed.insert(m_board);
                    }
                }
            }
        }
        
        //Remove front queue element
        open.pop();
    }
    return false;
}

void Sokoban::play() 
{
    std::string tmp_board = m_board;
    int tmp_agent = m_agent;
    std::string tmp_sol = "";
    
    system("clear");
    while(1)
    {
        bool tmp_push = false;
        print();
        if(isWin())
        {
            std::cout << "You win!" << std::endl;
            std::cout << "Your solution: "<< tmp_sol << std::endl;
            return;
        }
        if(isStuck())
        {
            std::cout << "You are stuck!" << std::endl;
            std::cout << "Input 'r' to reset." << std::endl;
        }
        std::cout << "Input: ";
        char key;
        std::cin >> key;

        system("clear");
 
        char tmp_dir = ' ';
        switch(key)
        {
        case 'a':
            move(-1,0,tmp_push);
            tmp_dir = 'l' - (32*tmp_push);
            break;
        case 's':
            move(0,1,tmp_push);
            tmp_dir = 'd' - (32*tmp_push);
            break;
        case 'd':
            move(1,0,tmp_push);
            tmp_dir = 'r' - (32*tmp_push);
            break;
        case 'w':
            move(0,-1,tmp_push);
            tmp_dir = 'u' - (32*tmp_push);
            break;
        case 'r':
            m_board = tmp_board;
            m_agent = tmp_agent;
            tmp_sol = "";
            break;
        default:
            return;
        }
        tmp_sol += tmp_dir;
    }
}

void Sokoban::playback(std::string t_solution)
{ 
    bool tmp_push = false;
    system("clear");
    print();
    for(unsigned int i = 0; i < t_solution.length(); i++)
    {   
        usleep(150000);
        switch(t_solution[i])
        {
        case 'u': case 'U':
            move(0,-i, tmp_push);
            break;
        case 'd': case 'D':
            move(0,1,tmp_push);
            break;
        case 'l': case 'L':
            move(-1,0,tmp_push);
            break;
        case 'r': case 'R':
            move(1,0,tmp_push);
            break;
        } 
        system("clear");
        print();
    }
}

void Sokoban::to_csv(std::string t_solution, 
    std::string t_filename = "directions")
{
    ;
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

        std::vector<size_t> tmp_edges = t_edges; // Remove warning for now
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
