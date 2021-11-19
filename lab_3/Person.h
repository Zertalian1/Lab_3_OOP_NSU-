#ifndef PER_H
#define PER_H
#include "Map.h"
class Person
{
public:
    virtual bool Move(const float& ElapsedTime, Map& map) = 0;   
    float PlayerX;      //  �����. Y
    float PlayerY;      //  �����. X
    float PlayerA;      //  ����������� �������
    float Speed;        //  �������� ������������
    float FOF_View;     //  ���� ���� ������
    float MRend_dist;   //  ��������� �������
    virtual ~Person() = default;
};

#endif //PER_H