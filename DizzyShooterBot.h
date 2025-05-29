#pragma once
#include "ShootingRobot.h"

class Unit;

class DizzyShooterBot : public ShootingRobot
{
    public:
        int robot_type = DIZZY_SHOOTER_BOT;
        DizzyShooterBot(Unit *unit);
        bool useAbility();
        bool useAbility(int x, int y);
        bool fire(int x, int y);
};