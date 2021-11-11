#include "Player.h"




Player::Player(const float& x, const float& y, const float& A,const float& view,const float& dist,const float& spead)
{
    PlayerX = x;
    PlayerY = y;
    PlayerA = A;
	Speed = spead;
    FOF_View = view;
    MRend_dist = dist;
}


bool Player::Move(const float& ElapsedTime, Map& map)
{
	if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
		PlayerA -= (Speed * 0.75f) * ElapsedTime;

	// Handle CW Rotation
	if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
		PlayerA += (Speed * 0.75f) * ElapsedTime;

	// Handle Forwards movement & collision
	if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
	{
		PlayerX += sinf(PlayerA) * Speed * ElapsedTime;;
		PlayerY += cosf(PlayerA) * Speed * ElapsedTime;;
		if (map.get_map().c_str()[(int)PlayerX * map.get_MapWidth() + (int)PlayerY] == '#')
		{
			PlayerX -= sinf(PlayerA) * Speed * ElapsedTime;;
			PlayerY -= cosf(PlayerA) * Speed * ElapsedTime;;
		}
	}
	if (GetAsyncKeyState(27) & 0x8000) {
		return 0;
	}

	// Handle backwards movement & collision
	if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
	{
		PlayerX -= sinf(PlayerA) * Speed * ElapsedTime;;
		PlayerY -= cosf(PlayerA) * Speed * ElapsedTime;;
		if (map.get_map().c_str()[(int)PlayerX * map.get_MapWidth() + (int)PlayerY] == '#')
		{
			PlayerX += sinf(PlayerA) * Speed * ElapsedTime;;
			PlayerY += cosf(PlayerA) * Speed * ElapsedTime;;
		}
	}

	return 1;
}



