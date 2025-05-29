#pragma once
#include "Unit.h"
#include "Evolutions.h"

class HawkingBot : public MoveBot
{
    public:
        int robot_type = BLIND_BOT;
        HawkingBot(Unit *unit);
        bool useAbility();
        bool useAbility(int x, int y) { return false; }; // its blind so no need value for x and y
};
