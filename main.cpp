#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Define data structure for holding coordinates
typedef struct 
{
    unsigned int x;
    unsigned int y;
} point;

typedef struct
{
    std::vector<std::vector<char>> box;
    std::vector<std::vector<char>> goal;
    std::vector<std::vector<char>> wall;
} board;

/*  Import map file:
    &map    String vector for storing each line.
    mapfile String name (and location) of file to be imported */
bool import(std::vector<std::string> &map, std::string filename)
{
    // Attempt to open map file
    std::ifstream mapfile;
    mapfile.open(filename);
    
    // Check if file can be opened (exists)
    if(!mapfile.is_open())
    {
        return false;
    }
    
    // Store contents of map file in map vector
    std::string mapline;
    while(!mapfile.eof())
    {   
        getline(mapfile,mapline);   // Save line to temp variable
        map.push_back(mapline);     // Push variable to map vector
    }
   
    // Close map file
    mapfile.close();

    return true;
}

/*  Print contents of board and player structures,
    in same map */
void print(board board, point player)
{    
    for(unsigned int i = 0; i < board.wall.size(); i++)
    {
        for(unsigned int j = 0; j < board.wall[i].size(); j++)
        {
            if(player.x == j && player.y == i)
            {
                std::cout << 'M';
            }
            else if(board.box[i][j] != ' ')
            {
                std::cout << board.box[i][j];
            }
            else if(board.goal[i][j] != ' ')
            {
                std::cout << board.goal[i][j];
            }
            else
            {
                std::cout << board.wall[i][j];
            }
        }
        std::cout << std::endl;
    }
}

/*  Map parser. Splits map up into various objects, 
    and stores them in board and player structures */
void parse(std::vector<std::string> map, board &board, point &player)
{
    /*  Character representation:
        .: walkable positions; 
        X: wall; 
        M: start position of robot; 
        J: start positions of cans; 
        G: Goal positions of cans;
    */
    std::vector<char> tmp_box;
    std::vector<char> tmp_goal;
    std::vector<char> tmp_wall;
    for(unsigned int i = 0; i < map.size(); i++)
    {
        for(unsigned int j = 0; j < map[i].size(); j++)
        {
            if(map[i][j] == ' ')
            {
                tmp_box.push_back(' ');
                tmp_goal.push_back(' ');
                tmp_wall.push_back(' ');
            }
            else if(map[i][j] == 'X' || map[i][j] == '.')
            {
                tmp_wall.push_back(map[i][j]);
                tmp_box.push_back(' ');
                tmp_goal.push_back(' ');
            }
            else if(map[i][j] == 'G')
            {
                tmp_wall.push_back('.');
                tmp_box.push_back(' ');
                tmp_goal.push_back(map[i][j]);
            }
            else if(map[i][j] == 'J')
            {
                tmp_wall.push_back('.');
                tmp_box.push_back(map[i][j]);
                tmp_goal.push_back(' ');
            }
            else if(map[i][j] == 'M')
            {
                tmp_wall.push_back('.');
                tmp_box.push_back(' ');
                tmp_goal.push_back(' ');
                player.x = j;
                player.y = i;
            }
        }
        board.wall.push_back(tmp_wall);
        board.box.push_back(tmp_box);
        board.goal.push_back(tmp_goal);
        tmp_wall.clear();
        tmp_box.clear();
        tmp_goal.clear();
    }
}

int main(int argc, char *argv[])
{  
    // Create filename and map variable (see 'import')
    std::string filename;
    std::vector<std::string> map;

/*  Check function argument count
    Note: We want 2 arguments:
        1) Function call
        2) Location of map file */
    if(argc != 2)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return -1;
    }
    else
    {
        filename = argv[1];     // Get filename
    }
    
    // Attempt to import map file
    if(!import(map, filename))
    {
        std::cout << "Failed to import file " << filename << std::endl;
        return -1;
    }
    
    // Create objects for storing parser results
    board Board;
    point Player;

    // parse and print map for demonstration
    parse(map, Board, Player);
    print(Board, Player);

    return 0;
}
