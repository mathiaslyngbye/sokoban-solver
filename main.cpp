#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "sokoban.hpp"

// Import data from filename, store in map, cols, and rows
bool import(std::string &t_map, 
            int &t_cols, 
            int &t_rows, 
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
    for(int i = 0; i != tmp_map.size(); i++)
    {
        if(tmp_map[i].length() > t_cols)
            t_cols = tmp_map[i].length();
    }

    // Store map in string
    for(int i = 0; i < t_rows; i++)
    {
        t_map += tmp_map[i];
        
        int space = (t_cols-tmp_map[i].length());
        std::cout << space << std::endl;
        if(space)
        {
            for(int i = 0; i < space; i++)
                t_map += ' ';
        }
    }

    mapfile.close();
    return true;
}

int main(int argc, char *argv[])
{  
    std::string map;
    int cols;
    int rows;

    if(argc != 2)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return -1;
    }
    else
    {
        std::string filename = argv[1];
        if(!import(map, cols, rows, filename))
        {
            std::cout << "Failed to import file " << filename << std::endl;
            return -1;
        }
    } 
    
    // Create sokoban board object
    Sokoban board(map, cols, rows);
    board.print();

    // Scuffed user input
    while(1)
    {
        system("clear");
        board.print();
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
