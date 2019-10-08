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

//  Import map file:
//  &map    String vector for storing each line.
//  mapfile String name (and location) of file to be imported 
bool import(std::vector<std::string> &t_map, std::string t_filename)
{
    // Attempt to open map file
    std::ifstream mapfile;
    mapfile.open(t_filename);
    
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
        t_map.push_back(mapline);     // Push variable to map vector
    }
   
    // Close map file
    mapfile.close();

    return true;
}

// Print contents of board and player structures,in same map
void print(board t_board, point t_player)
{    
    for(unsigned int i = 0; i < t_board.wall.size(); i++)
    {
        for(unsigned int j = 0; j < t_board.wall[i].size(); j++)
        {
            if(t_player.x == j && t_player.y == i)
            {
                std::cout << 'M';
            }
            else if(t_board.box[i][j] != ' ')
            {
                std::cout << t_board.box[i][j];
            }
            else if(t_board.goal[i][j] != ' ')
            {
                std::cout << t_board.goal[i][j];
            }
            else
            {
                std::cout << t_board.wall[i][j];
            }
        }
        std::cout << std::endl;
    }
}

// Map parser. Splits map up into various objects, 
// and stores them in board and player structures 
void parse(std::vector<std::string> t_map, board &t_board, point &t_player)
{
    //  Character representation:
    //  .: walkable positions; 
    //  X: wall; 
    //  M: start position of robot; 
    //  J: start positions of cans; 
    //  G: Goal positions of cans;

    std::vector<char> tmp_box;
    std::vector<char> tmp_goal;
    std::vector<char> tmp_wall;
    for(unsigned int i = 0; i < t_map.size(); i++)
    {
        for(unsigned int j = 0; j < t_map[i].size(); j++)
        {
            if(t_map[i][j] == ' ')
            {
                tmp_box.push_back(' ');
                tmp_goal.push_back(' ');
                tmp_wall.push_back(' ');
            }
            else if(t_map[i][j] == 'X' || t_map[i][j] == '.')
            {
                tmp_wall.push_back(t_map[i][j]);
                tmp_box.push_back(' ');
                tmp_goal.push_back(' ');
            }
            else if(t_map[i][j] == 'G')
            {
                tmp_wall.push_back('.');
                tmp_box.push_back(' ');
                tmp_goal.push_back(t_map[i][j]);
            }
            else if(t_map[i][j] == 'J')
            {
                tmp_wall.push_back('.');
                tmp_box.push_back(t_map[i][j]);
                tmp_goal.push_back(' ');
            }
            else if(t_map[i][j] == 'M')
            {
                tmp_wall.push_back('.');
                tmp_box.push_back(' ');
                tmp_goal.push_back(' ');
                t_player.x = j;
                t_player.y = i;
            }
        }
        t_board.wall.push_back(tmp_wall);
        t_board.box.push_back(tmp_box);
        t_board.goal.push_back(tmp_goal);
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

    // Check function argument count
    // Note: We want 2 arguments:
    // 1) Function call
    // 2) Location of map file 
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
    board testBoard;
    point testPlayer;

    // parse and print map for demonstration
    parse(map, testBoard, testPlayer);
    print(testBoard, testPlayer);

    return 0;
}
