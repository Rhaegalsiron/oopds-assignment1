#include "ScoutBot.h"
#include <iostream>
using namespace std;

ScoutBot::ScoutBot(Unit *unit)
{
    this->unit = unit;
    this->mapVisionCount = 3;
};

bool ScoutBot::useAbility(int x, int y)
{
    if (mapVisionCount <= 0)
    {   
        this->unit->log("No map vision uses remaining!");
        //cout << "No map vision uses remaining!" << endl;
        return false;
    }

    // Get the grid at the specified coordinates
    Grid *targetGrid = this->unit->field->getGrid(x, y);
    if (targetGrid == nullptr)
    {   
        this->unit->log("Invalid grid coordinates");
        //cout << "Invalid grid coordinates" << endl;
        return false;
    }

    // Check if there is a unit at the target grid
    if (targetGrid->occupyingUnit != nullptr)
    {
        Unit *targetUnit = targetGrid->occupyingUnit;
        this->unit->log("Unit found at (" + to_string(x) + "," + to_string(y) + "): " + targetUnit->Name);
        //cout << "Unit found at (" << x << "," << y << "): " << targetUnit->Name << endl;
    }
    else
    {   
        this->unit->log("No unit found at (" + to_string(x) + "," + to_string(y) + ").");
        //cout << "No unit found at (" << x << "," << y << ")." << endl;
    }

    // Lower mapVisionCount after use
    mapVisionCount--;
    return true;
}
