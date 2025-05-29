#include "GenericRobot.h"

GenericRobot::GenericRobot(Unit *unit)
{
    this->unit = unit;
    this->hitChance = 70;
}

bool GenericRobot::move(int x, int y)
{
    if (this->unit->isRespawning)
    {
        return false;
    }

    int deltaX = abs(this->unit->currentGrid->x - x);
    int deltaY = abs(this->unit->currentGrid->y - y);

    if (deltaX > 1 && x > this->unit->currentGrid->x)
    {
        x = this->unit->currentGrid->x + 1;
    }
    if (deltaX > 1 & x < this->unit->currentGrid->x)
    {
        x = this->unit->currentGrid->x - 1;
    }

    if (deltaY > 1 && y > this->unit->currentGrid->y)
    {
        y = this->unit->currentGrid->y + 1;
    }
    if (deltaY > 1 & y < this->unit->currentGrid->y)
    {
        y = this->unit->currentGrid->y - 1;
    }

    Vector2D clampedCoordinates = this->unit->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;

    bool isSuccefullyMoved = this->unit->updatePos(x, y);

    if (isSuccefullyMoved)
    {
        this->unit->log(this->unit->Name + " moved to coordinates (" + to_string(x) + "," + to_string(y) + ").");
    }

    return isSuccefullyMoved;
}

bool GenericRobot::fire(int x, int y)
{
    if (this->unit->isRespawning || this->unit->hasFired)
    {
        return false;
    }

    x = this->clampToLimit(this->unit->currentGrid->x, x, 1);
    y = this->clampToLimit(this->unit->currentGrid->y, y, 1);
    Vector2D clampedCoordinates = this->unit->field->clampToBattlefield(x, y);
    x = clampedCoordinates.x;
    y = clampedCoordinates.y;

    Grid *targetGrid = this->unit->field->getGrid(x, y);
    Unit *targetUnit = targetGrid->occupyingUnit;
    bool isSuccessfulHit = rand() % 100 < this->hitChance;
    this->unit->onFiring(targetUnit, isSuccessfulHit, x, y);
    return isSuccessfulHit;
}

bool GenericRobot::look(int x, int y)
{
    if (this->unit->isRespawning)
    {
        return false;
    }

    int deltaX = abs(this->unit->currentGrid->x - x);
    int deltaY = abs(this->unit->currentGrid->y - y);

    if (deltaX > 1 && x > this->unit->currentGrid->x)
    {
        x = this->unit->currentGrid->x + 1;
    }
    if (deltaX > 1 & x < this->unit->currentGrid->x)
    {
        x = this->unit->currentGrid->x - 1;
    }

    if (deltaY > 1 && y > this->unit->currentGrid->y)
    {
        y = this->unit->currentGrid->y + 1;
    }
    if (deltaY > 1 & y < this->unit->currentGrid->y)
    {
        y = this->unit->currentGrid->y - 1;
    }

    this->unit->seenUnit = this->unit->field->getGrid(x, y)->occupyingUnit;
    return this->unit->seenUnit != NULL;
}
