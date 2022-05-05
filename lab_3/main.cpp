#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Game_eng.h"
#include <map>
#include "TrapTeleport.h"

#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")

using namespace std;




int main()
{
	string map_name="Map1";
	Game_engen game;
	while (1) {
		int chose = game.Main_menu();
		if (chose) {
			map_name=game.Map_menu();
		}
		else {
			if (map_name != "error") {
				Game_engen game1(map_name);
				game = game1;
				break;
			}
		}
	}
	
	while (1) {
		game.Game_eng();
		if (game.Esc_menu())
			break;
	}
	return 0;
}