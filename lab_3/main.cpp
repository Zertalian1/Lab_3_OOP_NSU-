#include <iostream>
#include "Game_eng.h"
#include <map>
#include "Trap.h"

using namespace std;




int main()
{
	//std::map<std::pair<int, int>, Trap> traps;
	//traps.insert(pair<char, int>('a', 10));
	//Trap trap1(10);
	//traps[std::make_pair(0, 0)] = trap1;
	string map_name="Map1";
	Game_engen game;
	while (1) {
		int chose = game.Main_menu();
		if (chose) {
			map_name=game.Map_menu();
		}
		else {
			Game_engen game1(map_name);
			game = game1;
			break;
		}
	}
	
	while (1) {
		game.Game_eng();
		if (game.Esc_menu())
			break;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}