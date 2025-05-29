#pragma once
#include "MovingRobot.h"
#include "Ability.h"

class Unit;

class StealthBot : public MovingRobot
{
    public:
        int robot_type = STEALTH_BOT;
        StealthBot(Unit *unit);
        int hideCount = 3; // hide charges per match
        bool useAbility();
        bool useAbility(int x, int y);
        bool move(int x, int y);
};
