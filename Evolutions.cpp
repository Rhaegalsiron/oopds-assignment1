
#include "Evolutions.h"
#include <iostream>
using namespace std;

Robot::Robot(Unit *unit)
{
    this->unit = unit;
}

bool GenericRobot::move(int x, int y)
{
    if (x > 0)
    {
        x = 1;
    }
    else if (x < 0)
    {
        x = -1;
    }
    if (y > 0)
    {
        y = 1;
    }
    else if (y < 0)
    {
        y = -1;
    }
    this->unit->updatePos(x, y);
    return true;
}

bool GenericRobot::fire(int x, int y)
{
    // TODO: Move fire definition from Unit to here.
    return false;
}

bool GenericRobot::look(int x, int y)
{
    // TODO: Implement look.
    return false;
}

bool JumpBot::move(int x, int y)
{
    if (chargesRemaining <= 0)
    {
        return false;
    }
    this->unit->updatePos(x, y);
    chargesRemaining--;
    return true;
}
