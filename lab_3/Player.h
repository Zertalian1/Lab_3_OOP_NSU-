#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
using namespace std;

#include <stdio.h>
#include <Windows.h>
#include "Map.h"

class Player
{
private:
    float PlayerX;      //  коорд. Y
    float PlayerY;      //  коорд. X
    float PlayerA;      //  направление взгляда
    float Speed;        //  скорость передвижения
    float FOF_View;     //  угол поля зрения
    float MRend_dist;   //  дистанция взгляда

public:
    Player() {}
    Player(const float& x,const float& y,const float& A,const float& spead,const float& view,const float& dist); // добавить const type &
    //void Damage(const int& getting_d);      //  игрок получил урон
    bool Move(const float& ElapsedTime, Map& map);        //  двигвться    
    void set_X(const float& X) { PlayerX = X; }
    void set_Y(const float& Y) { PlayerY = Y; }
    const float& get_X() { return PlayerX; }
    const float& get_Y() { return PlayerY; }
    const float& get_A() { return PlayerA; }
    const float& get_FOV() { return FOF_View; }
    const float& get_Depth() { return MRend_dist; }

};
#endif //PLAYER_H   