#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool import(std::vector<std::string> &map, std::string filename)
{
    std::ifstream mapfile;
    mapfile.open(filename);
    
    if(!mapfile.is_open())
    {
        return false;
    }
    
    std::string mapline;
    while(!mapfile.eof())
    {   
        getline(mapfile,mapline);
        map.push_back(mapline);
    }
    
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
    
    for(std::vector<std::string>::iterator i = map.begin(); i != map.end(); ++i)
    {
        std::cout << *i << std::endl;
    }

    return 0;
}
