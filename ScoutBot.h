#pragma once
#include <iostream>
#include "Types.h"
#include "Robot.h"
#include "SeeingRobot.h"
#include "BattleField.h"
#include "AbstractGame.h"

#include "Directions.h"

class Unit;

class ScoutBot : public SeeingRobot
{
private:
    int mapVisionCount;

public:
    ScoutBot(Unit *unit);
    bool useAbility(int x, int y);
    bool useAbility();
    bool look(int x, int y);
};
