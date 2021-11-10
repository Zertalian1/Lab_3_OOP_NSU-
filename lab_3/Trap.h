#ifndef TRAP_H
#define TRAP_H
#include <string>


class Trap
{
private:
    int M_F_name;     //  урон ловушки

public:
    Trap(const int name);  
    const int& get_voice() { return M_F_name; }
};
#endif //TRAP_H  