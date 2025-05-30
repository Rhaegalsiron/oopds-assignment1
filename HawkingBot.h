#pragma once
#include "Unit.h"


class HawkingBot : public MovingRobot
{
    public:
        HawkingBot(Unit *unit);
        bool useAbility();
        bool useAbility(int x, int y); // its blind so no need value for x and y
        bool move(int x, int y);
};
