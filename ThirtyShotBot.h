#pragma once
#include <iostream>
#include "Types.h"
#include "ShootingRobot.h"
#include "BattleField.h"
#include "AbstractGame.h"

#include "Directions.h"

class Unit;

class ThirtyShotBot : public ShootingRobot
{
private:
    int magazineSize; // Magazine size for the bot

public:
    ThirtyShotBot(Unit *unit);
    bool useAbility(int x, int y); // Override the pure virtual function.
};
