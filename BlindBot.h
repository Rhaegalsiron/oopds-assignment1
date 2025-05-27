#pragma once
#include "Unit.h"
#include "Evolutions.h"

class BlindBot : public SeeingBot
{
    public:
        int robot_type = BLIND_BOT;
        BlindBot(Unit *unit);
        bool useAbility();
        bool useAbility(int x, int y) { return false; }; // its blind so no need value for x and y
};