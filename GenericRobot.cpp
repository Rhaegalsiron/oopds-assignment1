#include "GenericRobot.h"

GenericRobot::GenericRobot(Unit *unit)
{
    this->unit = unit;
    this->hitChance = 70;
}

bool GenericRobot::move(int x, int y)
{
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

    return this->unit->updatePos(x, y);
}

bool GenericRobot::fire(int x, int y)
{
    Grid *targetGrid = this->unit->field->getGrid(x, y);
    if (targetGrid->occupyingUnit != NULL)
    {
        bool successfulHit = rand() % 100 < this->hitChance;
        if (successfulHit)
        {
            targetGrid->occupyingUnit->destroy();
            return true;
        }
    }
    return false;
}

bool GenericRobot::look(int x, int y)
{
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
