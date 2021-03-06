#ifndef GAME_E_H
#define GAME_E_H
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include "Player.h"
#include "TrapTeleport.h"
#include <map> 
using namespace std;

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

class  Game_engen
{
public:
	Game_engen() {};
	Game_engen(const string& map_name);
	bool Main_menu();
	void Game_eng();
	bool Esc_menu();
	string Map_menu();
private:
	Player player;
	Map map_;
	map<std::pair<int, int>, shared_ptr<TrapTeleport>> traps;
	float Start_X;
	float Start_Y;
};
#endif //GAME_E_H