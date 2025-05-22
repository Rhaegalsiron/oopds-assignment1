#include "JumpBot.h"

JumpBot::JumpBot(Unit *unit)
{
    this->unit = unit;
}

bool JumpBot::useAbility(int x, int y)
{
    if (this->chargesRemaining<= 0)
    {
        return false;
    }
    this->unit->updatePos(x, y);
    this->unit->hasMoved = true; // set this flag hasMoved to true since the robot has moved.
    this->unit->messageLog.push_back(this->unit->Name + " jumped to coordinates ( " + to_string(x) + "," + to_string(y) + ").");
    this->chargesRemaining--;
    return true;
}