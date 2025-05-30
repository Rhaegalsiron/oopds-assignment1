#pragma once
#include "Unit.h"

class SemiAutoBot : public ShootingRobot
{
public:
    SemiAutoBot(Unit *unit);
    int burstSize = 3;
    bool useAbility(int x, int y);
    bool useAbility();
    bool fire(int x, int y);
};
