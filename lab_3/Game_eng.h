#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include "Player.h"
#include "Trap.h"
#include <map> 
using namespace std;

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

class  Game_engen
{
public:
	Game_engen() {}
	Game_engen(const string& map_name);
	bool Main_menu();
	void Game_eng();
	bool Esc_menu();
	bool Save();
	string Map_menu();
private:
	Player player;
	Map map_;
	map<std::pair<int, int>, shared_ptr<Trap>> traps;
	float Start_X;
	float Start_Y;
};