#pragma once
#include "ShootingRobot.h"

class Unit;

class DizzyShooterBot : public ShootingRobot
{
    public:
        DizzyShooterBot(Unit *unit);
        bool useAbility();
        bool useAbility(int x, int y);
        bool fire(int x, int y);
};