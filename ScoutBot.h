#pragma once
#include <iostream>
#include "Types.h"
#include "AbstractRobot.h"
#include "Unit.h"
#include "BattleField.h"
#include "AbstractGame.h"
#include "Evolutions.h"
#include "Directions.h"

class ScoutBot : public SeeingBot
{
    private:
        int mapVisionCount;

    public: 
        ScoutBot(Unit *unit);
        bool useAbility(int x, int y);
        bool useAbility() { return false; };
};
