#pragma once
#include "Unit.h"
#include "Evolutions.h"

class SemiAutoBot : public ActionBot
{
    int robot_type = SEMI_AUTO_BOT;
        SemiAutoBot(Unit *unit);
        int shellsRemaining = 10;
        bool useAbility (int x, int y);
        void afterFiring(Unit *targetUnit, bool isSuccessfulHit, int x, int y);
        //returns if another robot was successfully shot
};
