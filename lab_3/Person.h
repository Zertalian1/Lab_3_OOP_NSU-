#include "Map.h"
class Person
{
private:
    

public:
    virtual bool Move(const float& ElapsedTime, Map& map) = 0;   
    float PlayerX;      //  коорд. Y
    float PlayerY;      //  коорд. X
    float PlayerA;      //  направление взгляда
    float Speed;        //  скорость передвижения
    float FOF_View;     //  угол поля зрения
    float MRend_dist;   //  дистанция взгляда
};