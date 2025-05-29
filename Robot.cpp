#include "Robot.h"

int Robot::clampToLimit(int currentPos, int targetPos, int limit)
{
    int deltaPos = abs(currentPos - targetPos);
    if (deltaPos <= limit)
    {
        return targetPos;
    }
    if (targetPos < currentPos)
    {
        return currentPos - limit;
    }
    return currentPos + limit;
}

Unit *Robot::getUnit()
{
    return this->unit;
}

void Robot::setUnit(Unit *unit)
{
    this->unit = unit;
}