#pragma once
#include "Unit.h"
#include "Evolutions.h"

class SemiAutoBot : public ActionBot
{
    int robot_type = SEMI_AUTO_BOT;
        SemiAutoBot(Unit *unit);
        int burstSize = 3;
        bool useAbility (int x, int y);
};
