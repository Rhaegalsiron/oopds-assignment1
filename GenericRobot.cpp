
#include "GenericRobot.h"
#include <iostream>
using namespace std;

GenericRobot::GenericRobot(Unit *unit)
{
    this->unit = unit;
    this->hitChance = 70;
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
    this->unit->seenUnit = this->unit->field->getGrid(x,y)->occupyingUnit;
    return this->unit->seenUnit != NULL;
}
