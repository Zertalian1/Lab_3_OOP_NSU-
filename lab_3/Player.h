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
    float PlayerX;      //  �����. Y
    float PlayerY;      //  �����. X
    float PlayerA;      //  ����������� �������
    float Speed;        //  �������� ������������
    float FOF_View;     //  ���� ���� ������
    float MRend_dist;   //  ��������� �������

public:
    Player() {}
    Player(const float& x,const float& y,const float& A,const float& spead,const float& view,const float& dist); // �������� const type &
    //void Damage(const int& getting_d);      //  ����� ������� ����
    bool Move(const float& ElapsedTime, Map& map);        //  ���������    
    void set_X(const float& X) { PlayerX = X; }
    void set_Y(const float& Y) { PlayerY = Y; }
    const float& get_X() { return PlayerX; }
    const float& get_Y() { return PlayerY; }
    const float& get_A() { return PlayerA; }
    const float& get_FOV() { return FOF_View; }
    const float& get_Depth() { return MRend_dist; }

};
#endif //PLAYER_H   