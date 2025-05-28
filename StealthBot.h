#pragma once
#include "Unit.h"
#include "Evolutions.h"

class StealthBot : public MoveBot
{
    public:
        int robot_type = STEALTH_BOT;
        StealthBot(Unit *unit);
        int hideCount = 3; // hide charges per match
        bool useAbility();
        bool useAbility(int x, int y) {return false;}
};
