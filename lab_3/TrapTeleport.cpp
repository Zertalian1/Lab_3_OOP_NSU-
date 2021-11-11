#include "TrapTeleport.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

TrapTeleport::TrapTeleport(const int name)
{
	M_F_name = name;
}

bool TrapTeleport::Trap_work()
{
	wchar_t* wc = new wchar_t[30];
	wsprintf(wc, TEXT("play Trap%d.mp3"), M_F_name);
	mciSendString(wc, NULL, 0, NULL);
	return false;
}

