#include "Map.h"
#include <iostream>

Map::Map(int S_W, int S_H, int M_W, int M_H, std::string map_name)
{
    nScreenWidth = S_W;
    nScreenHeight = S_H;
    nMapWidth = M_W;
    nMapHeight = M_H;
    Map_name = map_name+".txt";
    if (!set_map())
        std::cerr << "Read map error";
}

bool Map::set_map()
{

    std::string line;
    std::ifstream fis(Map_name);

    if (!fis)
    {
        std::cerr << ("File " + Map_name + " cannot opened!");
        return false;
    }

    while (getline(fis, line))
        maps += (line);

    fis.close();

    return true;
}

int Map::operator[](const int& index) const
{
    return maps[index];
}
