#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "sokoban.hpp"

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


int main(int argc, char *argv[])
{  
    std::string filename;
    std::vector<std::string> map;

    if(argc != 2)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return -1;
    }
    else
    {
        filename = argv[1];
    }
    
    if(!import(map, filename))
    {
        std::cout << "Failed to import file " << filename << std::endl;
        return -1;
    }
    
    // Hardcoded test map
    std::string tmp_map = "";
    tmp_map += "  XXXXX ";
    tmp_map += "XXX...X ";
    tmp_map += "XGMJ..X ";
    tmp_map += "XXX.JGX ";
    tmp_map += "XGXXJ.X ";
    tmp_map += "X.X.G.XX";
    tmp_map += "XJ.JJJGX";
    tmp_map += "X...G..X";
    tmp_map += "XXXXXXXX";
    Sokoban board(tmp_map,9,8);
    board.print();  
    board.move(1,0);
    board.print();
    board.move(0,1);
    board.print();
    board.move(0,-1);
    board.print();
    return 0;
}
