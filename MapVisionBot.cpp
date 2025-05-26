#include "MapVisionBot.h"
#include <iostream>
using namespace std;

MapVisionBot::MapVisionBot(Unit *unit)
{
    this->unit = unit;
    this->mapVisionCount = 3;
};

bool MapVisionBot::lookSpecial(int x, int y)
{
    if (mapVisionCount <= 0)
    {
        cout << "No map vision uses remaining!" << endl;
        return false;
    }

    // Get the grid at the specified coordinates
    Grid *targetGrid = this->unit->field->getGrid(x, y);
    if (targetGrid == nullptr)
    {
        cout << "Invalid grid coordinates" << endl;
        return false;
    }

    // Check if there is a unit at the target grid
    if (targetGrid->occupyingUnit != nullptr)
    {
        Unit *targetUnit = targetGrid->occupyingUnit;
        cout << "Unit found at (" << x << ", " << y << "): " << targetUnit->Name << endl;
    }
    else
    {
        cout << "No unit found at (" << x << ", " << y << ")." << endl;
    }

    // Lower mapVisionCount after use
    mapVisionCount--;
    return true;
}
