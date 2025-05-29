#pragma once
#include <iostream>
#include "Types.h"
#include "AbstractRobot.h"
#include "Unit.h"
#include "BattleField.h"
#include "AbstractGame.h"
#include "Evolutions.h"
#include "Directions.h"


class ThirtyShotBot : public ActionBot
{
private:
    int magazineSize; // Magazine size for the bot

public:
    ThirtyShotBot(Unit *unit);
    bool useAbility(int x, int y) {
        return this->unit->fire(x, y);
    }//Override the pure virtual function.
};
