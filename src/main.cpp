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
    std::string map = "#######....##mJ..##..G.##....#######";
    size_t cols = 6;
    size_t rows = 6;
    
    // Attempt to import and override
    if(argc != 2 || !import(map, cols, rows, argv[1]))
        std::cout << "Import failed, using default map..." << std::endl;
    
    // Create sokoban board object
    Sokoban board(map, cols, rows);

    // Scuffed user input
    while(1)
    {
        system("clear");
        board.print();
        if(board.isWin())
        {
            std::cout << "You win!" << std::endl;
            return 0;       
        }
        std::cout << "Input: ";
        char key;
        std::cin >> key;

        switch(key)
        {
        case 'a':
            board.move(-1,0);
            break;
        case 's':
            board.move(0,1);
            break;
        case 'd':
            board.move(1,0);
            break;
        case 'w':
            board.move(0,-1);
            break;
        default:
            return 0;
        }
    }
    return 0;
}
