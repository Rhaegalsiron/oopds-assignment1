#include "TrackerBot.h"
#include <iostream>
using namespace std;

TrackerBot::TrackerBot(Unit *unit)
{
    this->unit = unit;
    this->trackerCount = 3; // Initialize tracker count
}

bool TrackerBot::lookSpecial(int x, int y)
{
    if (trackerCount <= 0)
    {
        cout << "No more trackers available!" << endl;
        return false;
    }

    // Get the grid at the specified coordinates
    Grid *targetGrid = this->unit->field->getGrid(x, y);
    if (targetGrid == nullptr || targetGrid->occupyingUnit == nullptr)
    {
        cout << "No enemy to track at (" << x << ", " << y << ")." << endl;
        return false;
    }

    // Add the robot on the current grid to the tracked targets
    Unit *targetUnit = targetGrid->occupyingUnit;
    trackedTargets.push_back(targetUnit);
    trackerCount--; // Decrement tracker count
    cout << "Tracking robot: " << targetUnit->Name << " at (" << x << ", " << y << ")." << endl;

    return true;
}

void TrackerBot::revealLocation()
{
    if (trackedTargets.empty())
    {
        cout << "No tracked robots to reveal." << endl;
        return;
    }

    for (Unit *trackedUnit : trackedTargets)
    {
        if (trackedUnit->currentGrid != nullptr)
        {
            int posX = trackedUnit->currentGrid->x;
            int posY = trackedUnit->currentGrid->y;
            cout << "Robot " << trackedUnit->Name << " revealed at position (" << posX << ", " << posY << ")." << endl;
        }
        else
        {
            cout << "Robot " << trackedUnit->Name << " is no longer on the battlefield." << endl;
        }
    }
}
