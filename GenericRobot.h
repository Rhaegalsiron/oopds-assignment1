#pragma once
#include "Evolutions.h"

class GenericRobot : public Robot
{
public:
    int robot_type = GENERIC_ROBOT;
    GenericRobot(Unit *unit);
    bool move(int x, int y);
    bool fire(int x, int y);
    bool look(int x, int y);
};