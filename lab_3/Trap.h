#ifndef TRAP_H
#define TRAP_H
#include <string>


class Trap
{
private:
    std::string M_F_name;     //  урон ловушки

public:
    Trap(const std::string& name);   
};
#endif //TRAP_H  