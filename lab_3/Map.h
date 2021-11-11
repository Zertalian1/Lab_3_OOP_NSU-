#ifndef MAP_H
#define MAP_H
#include <string>
#include <fstream>
#include <string>

class Map
{
public:
	Map(int S_W, int S_H, int M_W, int M_H, std::string map_name);
	bool set_map();
	const std::string& get_map(){
		return maps;
	}
	const int& get_MapWidth(){
		return nMapWidth;
	}
	const int& get_MapHeight(){
		return nMapHeight;
	}
	const int& get_ScreenWidth(){
		return nScreenWidth;
	}
	const int& get_ScreenHeight(){
		return nScreenHeight;
	}
	int operator[](const int& index) const;
	~Map() {  };
	Map()  {  };
private:
	int nScreenWidth;			// Console Screen Size X (columns)
	int nScreenHeight;			// Console Screen Size Y (rows)
	int nMapWidth;				// World Dimensions
	int nMapHeight;
	std::string Map_name;
	std::string maps;
};
#endif //MAP_H


