#pragma once
#include "Unit.h"
#include "Evolutions.h"

class LongShotBot : public ActionBot
{
   public:
        int robot_type = LONG_SHOT_BOT;
        LongShotBot(Unit *unit);
        int shellsRemaining = 10;
        bool useAbility (int x, int y);
        void afterFiring(Unit *targetUnit, bool isSuccessfulHit, int x, int y);
        //returns if another robot was successfully shot
};
