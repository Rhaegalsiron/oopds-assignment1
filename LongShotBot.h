#pragma once
#include "ShootingRobot.h"

class Unit;

class LongShotBot : public ShootingRobot
{
public:
        LongShotBot(Unit *unit);
        int shellsRemaining = 10;
        bool useAbility(int x, int y);
        bool useAbility();
        bool fire(int x, int y);
};
