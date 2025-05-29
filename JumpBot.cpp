#include "JumpBot.h"
#include "Unit.h"

JumpBot::JumpBot(Unit *unit)
{
    this->setUnit(unit);
}

bool JumpBot::useAbility(int x, int y)
{
    if (this->getUnit()->isRespawning)
    {
        return false;
    }

    if (this->chargesRemaining <= 0)
    {
        return false;
    }
    if (this->getUnit()->field->getGrid(x, y)->occupyingUnit != NULL)
    {
        return false;
    }
    this->getUnit()->updatePos(x, y);
    this->getUnit()->hasMoved = true; // set this flag hasMoved to true since the robot has moved.
    this->getUnit()->log(this->getUnit()->Name + " jumped to coordinates (" + to_string(x) + "," + to_string(y) + ").");
    this->chargesRemaining--;
    return true;
}

bool JumpBot::useAbility()
{
    return false;
}

bool JumpBot::move(int x, int y)
{
    return false;
}