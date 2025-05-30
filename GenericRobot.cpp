#include "GenericRobot.h"
#include "Unit.h"
#include "BattleField.h"

GenericRobot::GenericRobot(Unit *unit)
{
    this->robot_type = GENERIC_ROBOT;
    this->setUnit(unit);
    this->hitChance = 70;
}

bool GenericRobot::move(int x, int y)
{
    if (this->getUnit()->isRespawning)
    {
        return false;
    }

    int deltaX = abs(this->getUnit()->currentGrid->x - x);
    int deltaY = abs(this->getUnit()->currentGrid->y - y);

    if (deltaX > 1 && x > this->getUnit()->currentGrid->x)
    {
        x = this->getUnit()->currentGrid->x + 1;
    }
    if (deltaX > 1 & x < this->getUnit()->currentGrid->x)
    {
        x = this->getUnit()->currentGrid->x - 1;
    }

    if (deltaY > 1 && y > this->getUnit()->currentGrid->y)
    {
        y = this->getUnit()->currentGrid->y + 1;
    }
    if (deltaY > 1 & y < this->getUnit()->currentGrid->y)
    {
        y = this->getUnit()->currentGrid->y - 1;
    }

    Vector2D clampedCoordinates = this->getUnit()->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;

    bool isSuccefullyMoved = this->getUnit()->updatePos(x, y);

    if (isSuccefullyMoved)
    {
        this->getUnit()->log(this->getUnit()->Name + " moved to coordinates (" + to_string(x) + "," + to_string(y) + ").");
    }

    return isSuccefullyMoved;
}

bool GenericRobot::fire(int x, int y)
{
    if (this->getUnit()->isRespawning || this->getUnit()->hasFired)
    {
        return false;
    }

    x = this->clampToLimit(this->getUnit()->currentGrid->x, x, 1);
    y = this->clampToLimit(this->getUnit()->currentGrid->y, y, 1);
    Vector2D clampedCoordinates = this->getUnit()->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;

    Grid *targetGrid = this->getUnit()->field->getGrid(x, y);
    Unit *targetUnit = targetGrid->occupyingUnit;
    bool isSuccessfulHit = rand() % 100 < this->hitChance;
    this->getUnit()->onFiring(targetUnit, isSuccessfulHit, x, y);
    return isSuccessfulHit;
}

bool GenericRobot::look(int x, int y)
{
    if (this->getUnit()->isRespawning)
    {
        return false;
    }

    int deltaX = abs(this->getUnit()->currentGrid->x - x);
    int deltaY = abs(this->getUnit()->currentGrid->y - y);

    if (deltaX > 1 && x > this->getUnit()->currentGrid->x)
    {
        x = this->getUnit()->currentGrid->x + 1;
    }
    if (deltaX > 1 & x < this->getUnit()->currentGrid->x)
    {
        x = this->getUnit()->currentGrid->x - 1;
    }

    if (deltaY > 1 && y > this->getUnit()->currentGrid->y)
    {
        y = this->getUnit()->currentGrid->y + 1;
    }
    if (deltaY > 1 & y < this->getUnit()->currentGrid->y)
    {
        y = this->getUnit()->currentGrid->y - 1;
    }

    this->getUnit()->seenUnit = this->getUnit()->field->getGrid(x, y)->occupyingUnit;
    return this->getUnit()->seenUnit != NULL;
}

bool GenericRobot::useAbility()
{
    return false;
}

bool GenericRobot::useAbility(int x, int y)
{
    return false;
}