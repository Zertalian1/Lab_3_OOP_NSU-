#include "Map.h"
class Person
{
private:
    

public:
    virtual bool Move(const float& ElapsedTime, Map& map) = 0;   
    float PlayerX;      //  �����. Y
    float PlayerY;      //  �����. X
    float PlayerA;      //  ����������� �������
    float Speed;        //  �������� ������������
    float FOF_View;     //  ���� ���� ������
    float MRend_dist;   //  ��������� �������
};