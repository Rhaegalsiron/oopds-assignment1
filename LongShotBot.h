#pragma once
#include "ShootingRobot.h"

class Unit;

class LongShotBot : public ShootingRobot
{
public:
        int robot_type = LONG_SHOT_BOT;
        LongShotBot(Unit *unit);
        int shellsRemaining = 10;
        bool useAbility(int x, int y);
};
