#pragma once
#include "Unit.h"
#include "Evolutions.h"

class DizzyShooterBot : public ActionBot
{
    public:
        int robot_type = DIZZY_SHOOTER_BOT;
        DizzyShooterBot(Unit *unit);
        bool useAbility();
        bool useAbility(int x, int y) { return false; };
};