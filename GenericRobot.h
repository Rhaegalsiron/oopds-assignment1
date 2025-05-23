#pragma once
#include "Evolutions.h"

class GenericRobot : public Robot
{
public:
    GenericRobot(Unit *unit);
    bool useAbility() { return false; };
    bool useAbility(int x, int y) { return false; };
    bool useAbility(Unit *unit) { return false; };
    bool move(int x, int y);
    bool fire(int x, int y);
    bool look(int x, int y);
};