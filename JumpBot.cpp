#include "JumpBot.h"

JumpBot::JumpBot(Unit *unit)
{
    this->unit = unit;
}

bool JumpBot::useAbility(int x, int y)
{
    if (this->unit->isRespawning) {
        return false;
    }

    if (this->chargesRemaining <= 0)
    {
        return false;
    }
    if (this->unit->field->getGrid(x, y)->occupyingUnit != NULL)
    {
        return false;
    }
    this->unit->updatePos(x, y);
    this->unit->hasMoved = true; // set this flag hasMoved to true since the robot has moved.
    this->unit->log(this->unit->Name + " jumped to coordinates (" + to_string(x) + "," + to_string(y) + ").");
    this->chargesRemaining--;
    return true;
}