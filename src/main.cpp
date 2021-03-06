#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "sokoban.hpp"

// Import data from filename, store in map, cols, and rows
bool import(std::string &t_map, 
            size_t &t_cols, 
            size_t &t_rows, 
            std::string t_filename)
{
    // Attempt to open map file
    std::ifstream mapfile;
    mapfile.open(t_filename);
    
    // Check if file can be opened (exists)
    if(!mapfile.is_open())
        return false;
   
    // Store contents of map file in map vector
    std::vector<std::string> tmp_map;
    std::string tmp_map_line;
    while(!mapfile.eof())
    {   
        getline(mapfile, tmp_map_line);
        tmp_map.push_back(tmp_map_line);
    }
   
    // Find dimensions
    t_cols = 0;
    t_rows = tmp_map.size()-1;
    for(unsigned int i = 0; i != tmp_map.size(); i++)
    {
        if(tmp_map[i].length() > t_cols)
            t_cols = tmp_map[i].length();
    }

    // Store map in string
    t_map = "";
    for(unsigned int i = 0; i < t_rows; i++)
    {
        t_map += tmp_map[i]; 
        unsigned int space = (t_cols-tmp_map[i].length());
        if(space)
        {
            for(unsigned int j = 0; j < space; j++)
                t_map += ' ';
        }
    }

    mapfile.close();
    return true;
}

int main(int argc, char *argv[])
{ 
    // Initialize map with defaults
    std::string map =   "XXXXXX";
    map +=              "X....X";
    map +=              "XMJ..X";
    map +=              "X....X";
    map +=              "X...GX";
    map +=              "XXXXXX";
    size_t cols = 6;
    size_t rows = 6;
    
    // Attempt to import and override
    std::cout << "Importing map file... ";
    if(argc != 2 || !import(map, cols, rows, argv[1]))
    {
        std::cout << "Failed!" << std::endl;
        std::cout << "Using default map... ";
    }
    std::cout << "Done!" << std::endl;
    
    // Create sokoban board object
    Sokoban board(map, cols, rows);  
    //board.print(); 
    
    // Solve
    std::string solution = "";
    if(board.solve(solution))
       board.to_csv(solution,"instructions");

    //board = Sokoban(map, cols, rows);
    //board.playback(solution);
    
    return 0;
}
