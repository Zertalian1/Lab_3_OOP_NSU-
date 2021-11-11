#ifndef TRAP_H
#define TRAP_H
#include <string>
#include "Trap.h"


class TrapTeleport : public Trap
{
private:
    int M_F_name;     //  урон ловушки

public:
    TrapTeleport(const int name);
    bool Trap_work() override;
};
#endif //TRAP_H  