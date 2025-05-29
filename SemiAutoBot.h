#pragma once
#include "Unit.h"

class SemiAutoBot : public ShootingRobot
{
public:
    int robot_type = SEMI_AUTO_BOT;
    SemiAutoBot(Unit *unit);
    int burstSize = 3;
    bool useAbility(int x, int y);
    bool fire(int x, int y);
};
